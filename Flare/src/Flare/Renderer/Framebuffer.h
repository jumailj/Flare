#pragma once
#include <Flare/Core/Core.h>

namespace Flare
{
    struct FramebufferSpecification
    {
        uint32_t Widht = 0, Height = 0;
        uint32_t samples = 1;

        bool SwapChainTarget = false;
        //glbindframebuffer(0)

    };


    class Framebuffer{
    public:
        virtual ~Framebuffer() = default;
        virtual void Bind() = 0;
        virtual void Unbind()  = 0;


        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;

       //  virtual FramebufferSpecification& GetSpecification() = 0; //todo implement function;
        virtual const FramebufferSpecification& GetSpecification() const = 0;
        static Ref<Framebuffer>Create(const FramebufferSpecification&spec);

    };
} // namespace Flare
