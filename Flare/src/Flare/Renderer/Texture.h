#pragma once
#include <cstdint>
#include <string>
#include <Flare/Core/Core.h>

namespace Flare{

    class Texture 
    {

    public:
        virtual~Texture() = default;
        virtual uint32_t GetWidht() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

    };

    class Texture2D: public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& path);


    };

}