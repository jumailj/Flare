#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Flare{


    ////// VERTEX-BUFFER /////

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) 
    {
        glCreateBuffers(1, &m_RenderID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr,GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) 
    {
        glCreateBuffers(1, &m_RenderID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices,GL_STATIC_DRAW);
        
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RenderID);
    }

    void OpenGLVertexBuffer::Bind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
    }

    void OpenGLVertexBuffer::Unbind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetData(const void* data, uint32_t size) 
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
        glBufferSubData(GL_ARRAY_BUFFER,0, size, data);
    }




    //// INDEX-BUFFER //////
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
    :m_Count(count)
    {
        glCreateBuffers(1,&m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count* sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


}