#include "Framebuffer.h"

#include <Flare/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLFramebuffer.h>

namespace Flare
{
  
      Flare::Ref<Flare::Framebuffer> Framebuffer::Create(const FramebufferSpecification&spec)
      {

        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLFrameBuffer>(spec);
        }

        LOG_ERROR("[FRAME BUFFER] Unknown RendereAPI");
        return nullptr;
      }
    
} 
