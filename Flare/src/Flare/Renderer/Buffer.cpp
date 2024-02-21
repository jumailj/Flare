#include "Buffer.h"


#include "Renderer.h"
#include <Platform/OpenGL/OpenGLBuffer.h>

#include <Flare/Core/Log.h>

namespace Flare{


    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) 
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
        case RendererAPI::API::OpenGL : return CreateRef<OpenGLVertexBuffer>(size);
        }
        LOG_ERROR("unknown RendereAPI");
        return nullptr;

    }


     Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
        case RendererAPI::API::OpenGL : return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        LOG_ERROR("unknown RendereAPI");
        return nullptr;
        
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count )
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
        case RendererAPI::API::OpenGL : return CreateRef<OpenGLIndexBuffer>(indices, count);
        }

        LOG_ERROR("unknown RendereAPI");
        return nullptr;

    }
}