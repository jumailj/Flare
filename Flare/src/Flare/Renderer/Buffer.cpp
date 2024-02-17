#include "Buffer.h"


#include "Renderer.h"
#include <Platform/OpenGL/OpenGLBuffer.h>

#include <Flare/Core/Log.h>

namespace Flare{

     Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
        case RendererAPI::API::OpenGL : return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }

        LOG_ERROR("unknown RendereAPI");
        return nullptr;
        
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size )
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
        case RendererAPI::API::OpenGL : return std::make_shared<OpenGLIndexBuffer>(indices, size);
        }

        LOG_ERROR("unknown RendereAPI");
        return nullptr;

    }
}