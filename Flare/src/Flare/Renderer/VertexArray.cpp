#include "VertexArray.h"

#include "Renderer.h"
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Flare{

    
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
            case RendererAPI::OpenGL : return new OpenGLVertexArray();
        }

        LOG_ERROR("unknown RendereAPI");
        return nullptr;

    }


}