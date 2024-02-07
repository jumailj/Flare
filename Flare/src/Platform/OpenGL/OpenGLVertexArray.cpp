
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Flare{

        static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch(type) 
        {
            case ShaderDataType::Float: return  GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3: return  GL_FLOAT;
            case ShaderDataType::Mat4: return GL_FLOAT;;
            case ShaderDataType::Int: return GL_INT;
            case ShaderDataType::Int2: return GL_INT;
            case ShaderDataType::Int3: return GL_INT;
            case ShaderDataType::Int4: return GL_INT;
            case ShaderDataType::Bool : return GL_BOOL;
        }
        LOG_ERROR("UNKNOW SHADERDATA TYPE!");
        return 0;
        }


        OpenGLVertexArray::OpenGLVertexArray() 
        {
            glCreateVertexArrays(1, &m_RendererID);
        }

        void OpenGLVertexArray::Bind() const 
        {
            glBindVertexArray(m_RendererID);

        }

        void OpenGLVertexArray::Unbind() const 
        {
            glBindVertexArray(0);
        }

        void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
        {
            glBindVertexArray(m_RendererID);
            vertexBuffer->Bind();

            // loging errors
            LOG_ERROR("");

            uint32_t index = 0;
            const auto& layout = vertexBuffer->GetLayout();

            for (const auto& element: layout)
            {
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index,element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));  
                index++;
            }
            m_VertexBuffers.push_back(vertexBuffer);
        }

        void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>&indexBuffer)
        {
            glBindVertexArray(m_RendererID);
            indexBuffer->Bind();

            m_IndexBuffer = indexBuffer;

        }

}