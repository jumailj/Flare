#pragma once

#include <Flare/Renderer/Framebuffer.h>

/* Memory buffer that contains data for all the pixels in a video frame*/
namespace Flare
{
    class OpenGLFrameBuffer: public Framebuffer
    {
    public:
        OpenGLFrameBuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFrameBuffer();

        void Invalidate();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual uint32_t GetColorAttachmentRendererID() const override {return m_ColorAttachment;}


        virtual const FramebufferSpecification& GetSpecification() const override {return m_Specification;}

    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0,m_DepthAttachment = 0;
        FramebufferSpecification m_Specification;
    };

    
} // namespace Flare

