#include "ScriptGlue.h"

#include "mono/metadata/object.h"
#include <Flare/Core/Log.h>

namespace Flare{

// #define FL_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Flare.InternalCalls::" #Name, Name)

    static void CppFunc() {
        LOG_TRACE("{0}", " written in c++, Hello from C++ function!");
    }

    struct Vector3 {
        float x, y, z;
    };

    static void NativeLogFunc(MonoString* parameter, int value){
        char* cstr = mono_string_to_utf8(parameter);
        std::string str(cstr);
        mono_free((void*)cstr);
        LOG_TRACE("{0} and {1}", str, value);
        
    }

    static void NativeLogFunc_Vector(Vector3* parameter) {
        if (!parameter) {
            LOG_TRACE("NativeLogFunc_Vector received a null vector!");
            return;
        }
    
        LOG_TRACE("vec : {0}, {1}, {2}", parameter->x, parameter->y, parameter->z);
    }



    void ScriptGlue::RegisterFunctions()
    {
        mono_add_internal_call("Flare.InternalCalls::NativeLog", (const void*)NativeLogFunc);
        mono_add_internal_call("Flare.InternalCalls::NativeLog_vector", (const void*)NativeLogFunc_Vector);
    }

}