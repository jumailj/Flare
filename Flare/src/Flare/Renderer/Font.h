#pragma once 

#include <filesystem>
#include "msdf-atlas-gen.h"

namespace Flare {

    class Font{
        public:
            Font(const std::filesystem::path & filepath);
    };

}