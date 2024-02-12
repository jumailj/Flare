#include "Texture.h"

#include "Renderer.h"
#include <Platform/OpenGL/OpenGLTexture.h>


namespace Flare{

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return std::make_shared<OpenGLTexture2D>(path);
        }

        LOG_ERROR("[VERTEX ARRAY] Unknown RendereAPI");
        return nullptr;

    }

}