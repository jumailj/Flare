#include "Buffer.h"


#include "Renderer.h"
#include <Platform/OpenGL/OpenGLBuffer.h>

#include <Flare/Core/Log.h>

namespace Flare{

     VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
        case RendererAPI::OpenGL : return new OpenGLVertexBuffer(vertices, size);
        }

        LOG_ERROR("unknown RendereAPI");
        return nullptr;
        
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size )
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None : LOG_ERROR("RendererAPI::None is currenlty not supported!"); return nullptr;
        case RendererAPI::OpenGL : return new OpenGLIndexBuffer(indices, size);
        }

        LOG_ERROR("unknown RendereAPI");
        return nullptr;

    }
}