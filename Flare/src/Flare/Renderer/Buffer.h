#pragma once
#include <cstdint>

//pure virutal interface, no implementaion, no data, zero storage. (v-table)
namespace Flare{

    // vertex buffer;
    class VertexBuffer{

    public:
        virtual ~VertexBuffer(){}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        //pointer
        static VertexBuffer* Create(float* vertices, uint32_t size);

        
    };

    // index buffer
    class IndexBuffer{
    public:

        virtual~IndexBuffer(){}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual int32_t GetCount() const = 0;

        //pointer
        static IndexBuffer* Create(uint32_t* indices, uint32_t size );

    };

}