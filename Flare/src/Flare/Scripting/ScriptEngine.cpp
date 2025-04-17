#include "ScriptEngine.h"
#include "ScriptGlue.h"

# include <Flare/Core/Log.h>

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/object.h"
#include "mono/metadata/mono-config.h"
#include "mono/metadata/debug-helpers.h"

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

// mono error on flare::scene::copy , scene.cpp
// Flare::EditorLayer::OnScenePlay.



namespace Flare {

    namespace Utils{
        //todo , move to filsystem class.
        static char* ReadBytes(const std::filesystem::path& filepath, uint32_t* outSize) {
            std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
            if (!stream) {
                std::cerr << "Failed to open file: " << filepath << std::endl;
                return nullptr;
            }
    
            std::streampos end = stream.tellg();
            stream.seekg(0, std::ios::beg);
            uint32_t size = end - stream.tellg();
    
            if (size == 0) {
                std::cerr << "File is empty: " << filepath << std::endl;
                return nullptr;
            }
    
            char* buffer = new char[size];
            stream.read(buffer, size);
            stream.close();
    
            *outSize = size;
            return buffer;
        }

        static MonoAssembly* LoadMonoAssembly(const std::filesystem::path& assemblyPath) {
            uint32_t fileSize = 0;
            char* fileData = ReadBytes(assemblyPath, &fileSize);
    
            if (!fileData) {
                std::cerr << "Failed to read assembly file: " << assemblyPath << std::endl;
                return nullptr;
            }
    
            MonoImageOpenStatus status;
            MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);
    
            if (status != MONO_IMAGE_OK) {
                std::cerr << "Failed to open Mono image from data: " << assemblyPath << std::endl;
                delete[] fileData;
                return nullptr;
            }


            std::string pathString = assemblyPath.string();
            MonoAssembly* assembly = mono_assembly_load_from_full(image, pathString.c_str(), &status, 0);
            mono_image_close(image);
            delete[] fileData;
    
            if (!assembly) {
                std::cerr << "Failed to load Mono assembly: " << assemblyPath << std::endl;
            }
    
            return assembly;
        }

        void PrintAssemblyTypes(MonoAssembly* assembly)
		{
			MonoImage* image = mono_assembly_get_image(assembly);
			const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
			int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

			for (int32_t i = 0; i < numTypes; i++)
			{
				uint32_t cols[MONO_TYPEDEF_SIZE];
				mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

				const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
				const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
			}
		}



    }


    struct ScriptEngineData {
        MonoDomain* RootDomain = nullptr;
        MonoDomain* AppDomain = nullptr;

        MonoAssembly* CoreAssembly = nullptr;
        MonoImage* CoreAssemblyImage = nullptr;

        ScriptClass EntityClass;
    };

    static ScriptEngineData* s_Data = nullptr;

 
    void ScriptEngine::Init() {


        s_Data = new ScriptEngineData();

        InitMono();
        LoadAssembly("Resource/Scripts/Flare-ScriptCore.dll");
        ScriptGlue::RegisterFunctions();


        s_Data->EntityClass = ScriptClass("Flare", "Entity");
        MonoObject* instance = s_Data->EntityClass.Instantiate();


        // --         ---           --- Rest of the code:  PrintMessage Function:
		MonoMethod* printMessageFunc = s_Data->EntityClass.GetMethod( "PrintMessage", 0);
        s_Data->EntityClass.InvokeMethod(instance, printMessageFunc, nullptr);


		// --         ---           --- Rest of the code:  PrintInt Function:
		MonoMethod* printIntFunc = s_Data->EntityClass.GetMethod("PrintInt", 1); 
		int value =5;
		void * param = &value;
		s_Data->EntityClass.InvokeMethod(instance, printIntFunc, &param);


		// --         ---           --- Rest of the code:  PrintInts Function:
		MonoMethod* printIntsFunc = s_Data->EntityClass.GetMethod("PrintInts", 2); 
		int value2 = 508;
		void* params[2] = {
			&value,
			&value2
		};
        s_Data->EntityClass.InvokeMethod(instance, printIntsFunc, params);



        // ---           --             --- Rest of the code:  PrintString Function:
        MonoString* monoString = mono_string_new(s_Data->AppDomain, "Hello world from c++");
		MonoMethod* printStringFunc = s_Data->EntityClass.GetMethod("PrintCustomMessage", 1);
        void *stringParam = monoString;
        s_Data->EntityClass.InvokeMethod(instance,printStringFunc, &stringParam );

    }


    void ScriptEngine::Shutdown() {
        ShutdownMono();
        delete s_Data;
        s_Data = nullptr;
    }

    void ScriptEngine::LoadAssembly(const std::filesystem::path &filepath)
    {

         // Set the root domain
         s_Data->AppDomain = mono_domain_create_appdomain(const_cast<char*>("FlareScriptRuntime"), nullptr);
         if (!s_Data->AppDomain) {
             LOG_ERROR("Failed to create Mono AppDomain!");
             return;
         }

         mono_domain_set(s_Data->AppDomain, true);
 
 
         // Load the C# assembly   Resource/Scripts/Flare-ScriptCore.dll
         // Make sure to use the correct path to your assembly
        std::string assemblyPath = filepath;
        s_Data->CoreAssembly = Utils::LoadMonoAssembly(assemblyPath);  if (!s_Data->CoreAssembly) {LOG_ERROR("Failed to load C# assembly from path: {0}", assemblyPath.c_str());return;}

        // Get the MonoImage from the assembly
        s_Data->CoreAssemblyImage = mono_assembly_get_image(s_Data->CoreAssembly); if (!s_Data->CoreAssemblyImage) { LOG_ERROR("Faild to get Mono assembly imfrom!"); return;}

    }

    void ScriptEngine::InitMono() {
        mono_config_parse(nullptr); // Load Mono configuration
        mono_set_assemblies_path("Resource/mono/lib");

        MonoDomain* rootDomain = mono_jit_init("FlareJITRuntime");
        if (!rootDomain) {
            LOG_ERROR("Failed to initialize Mono JIT runtime!");
            return;
        }
        s_Data->RootDomain = rootDomain;

    }

    void ScriptEngine::ShutdownMono() {
        if (s_Data->AppDomain) {
            mono_domain_unload(s_Data->AppDomain);
            s_Data->AppDomain = nullptr;
        }

        if (s_Data->RootDomain) {
            mono_jit_cleanup(s_Data->RootDomain);
            s_Data->RootDomain = nullptr;
        }
    }

          
    ScriptClass::ScriptClass(const std::string& classNamespace, const std::string& className)
    : m_ClassNamespace(classNamespace), m_ClassName(className)
    {
        m_MonoClass =  mono_class_from_name(s_Data->CoreAssemblyImage, classNamespace.c_str(), className.c_str()); 
    }

    MonoObject* ScriptClass::Instantiate()
    {
        return ScriptEngine::InstantiateClass(m_MonoClass);
    }

    MonoObject* ScriptEngine::InstantiateClass(MonoClass* monoClass){

        MonoObject* instance = mono_object_new(s_Data->AppDomain, monoClass);

        MonoObject* exception = nullptr; 
        mono_runtime_object_init(instance);

        if (exception) {
            MonoString* exceptionMessage = mono_object_to_string(exception, nullptr);
            const char* exceptionCStr = mono_string_to_utf8(exceptionMessage);
            std::cerr << "Exception occurred during object initialization: " << exceptionCStr << std::endl;
            mono_free((void*)exceptionCStr);
        }
        return instance;
            
    }

    MonoMethod* ScriptClass::GetMethod(const std::string& name, int parameterCount){
        return mono_class_get_method_from_name(m_MonoClass, name.c_str(), parameterCount);
    }

    MonoObject* ScriptClass::InvokeMethod(MonoObject* instance, MonoMethod* method, void** params){
        return mono_runtime_invoke(method, instance, params, nullptr);
    }

} // namespace Flare