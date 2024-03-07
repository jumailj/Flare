#pragma once

#include <string>

namespace Flare
{

    class FileDialogs
    {
    public:

        static void Init();

        //return the empty sting if cancelled!
        static std::string OpenFile(const char* filter);
        static std::string SaveFile(const char* filter);
    };


}