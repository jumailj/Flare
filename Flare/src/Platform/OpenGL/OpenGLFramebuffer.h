#pragma once

#include <Flare/Renderer/Framebuffer.h>
#include <Flare/Core/Log.h>

/* Memory buffer that contains data for all the pixels in a video frame*/
namespace Flare
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override 
		{ 
            if( index > m_ColorAttachments.size())
            {

				LOG_ERROR("index = {0} ColorAttachments = {1}", index,m_ColorAttachments.size());
                LOG_ERROR("index is larger than colorAttachment size");

            } 
            return m_ColorAttachments[index]; 
		}

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;
		FramebufferSpecification m_Specification;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
} // namespace Flare

