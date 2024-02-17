#include "VertexArray.h"

#include "Renderer.h"
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Flare{

    
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
            case RendererAPI::API::OpenGL : return std::make_shared<OpenGLVertexArray>();
        }

        LOG_ERROR("[VERTEX ARRAY] Unknown RendereAPI");
        return nullptr;

    }


}