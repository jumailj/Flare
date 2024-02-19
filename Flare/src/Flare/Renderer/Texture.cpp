#include "Texture.h"

#include "Renderer.h"
#include <Platform/OpenGL/OpenGLTexture.h>


namespace Flare{

    Ref<Texture2D> Texture2D::Create(uint32_t widht, uint32_t height) 
    {
        switch (Renderer::GetAPI())
        {

            case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLTexture2D>(widht,height);
        }

        return nullptr;

    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLTexture2D>(path);
        }

        LOG_ERROR("[VERTEX ARRAY] Unknown RendereAPI");
        return nullptr;

    }

}