#include "ScriptEngine.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/object.h"
#include "mono/metadata/mono-config.h"
#include "mono/metadata/debug-helpers.h"

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>


namespace Flare {

    struct ScriptEngineData {
        MonoDomain* RootDomain = nullptr;
        MonoDomain* AppDomain = nullptr;
        MonoAssembly* CoreAssembly = nullptr;
    };

    static ScriptEngineData* s_Data = nullptr;

    void ScriptEngine::Init() {
        s_Data = new ScriptEngineData();
        InitMono();
    }

    void ScriptEngine::Shutdown() {
        ShutdownMono();
        delete s_Data;
        s_Data = nullptr;
    }

    char* ReadBytes(const std::string& filepath, uint32_t* outSize) {
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

    MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath) {
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

        MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
        mono_image_close(image);
        delete[] fileData;

        if (!assembly) {
            std::cerr << "Failed to load Mono assembly: " << assemblyPath << std::endl;
        }

        return assembly;
    }

    void ScriptEngine::InitMono() {
        mono_config_parse(nullptr); // Load Mono configuration
        mono_set_assemblies_path("Resource/mono/lib");

        MonoDomain* rootDomain = mono_jit_init("FlareJITRuntime");
        if (!rootDomain) {
            std::cerr << "Failed to initialize Mono JIT runtime!" << std::endl;
            return;
        }
        s_Data->RootDomain = rootDomain;

        s_Data->AppDomain = mono_domain_create_appdomain(const_cast<char*>("FlareScriptRuntime"), nullptr);
        if (!s_Data->AppDomain) {
            std::cerr << "Failed to create Mono AppDomain!" << std::endl;
            return;
        }
        mono_domain_set(s_Data->AppDomain, true);

        std::string assemblyPath = "Resource/Scripts/Flare-ScriptCore.dll";
        s_Data->CoreAssembly = LoadCSharpAssembly(assemblyPath);
        if (!s_Data->CoreAssembly) {
            std::cerr << "Failed to load C# assembly from path: " << assemblyPath << std::endl;
            return;
        }

        MonoImage* assemblyImage = mono_assembly_get_image(s_Data->CoreAssembly);
        if (!assemblyImage) {
            std::cerr << "Failed to get Mono assembly image!" << std::endl;
            return;
        }

        MonoClass* monoClass = mono_class_from_name(assemblyImage, "Flare", "Main");
        if (!monoClass) {
            std::cerr << "Failed to find class 'Flare.Main' in the assembly!" << std::endl;
            return;
        }

        MonoObject* instance = mono_object_new(s_Data->AppDomain, monoClass);
        if (!instance) {
            std::cerr << "Failed to create an instance of 'Flare.Main'!" << std::endl;
            return;
        }

        MonoObject* exception = nullptr;
        mono_runtime_object_init(instance);

        if (exception) {
            MonoString* exceptionMessage = mono_object_to_string(exception, nullptr);
            const char* exceptionCStr = mono_string_to_utf8(exceptionMessage);
            std::cerr << "Exception occurred during object initialization: " << exceptionCStr << std::endl;
            mono_free((void*)exceptionCStr);
        }


		// --         ---           --- Rest of the code: 
		MonoMethod* printMessageFunc = mono_class_get_method_from_name(monoClass, "PrintMessage", 0);
		mono_runtime_invoke(printMessageFunc, instance, nullptr, nullptr);

		






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

} // namespace Flare