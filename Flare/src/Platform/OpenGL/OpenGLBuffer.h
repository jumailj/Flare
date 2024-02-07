#include <Flare/Renderer/Buffer.h>


namespace Flare{

    class OpenGLVertexBuffer: public VertexBuffer 
    {
    public:
        OpenGLVertexBuffer(float * vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;


    private:
    uint32_t m_RenderID;

    };

    class OpenGLIndexBuffer: public IndexBuffer
    {
    public:

        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;

        virtual int32_t GetCount() const {
            return m_Count;
        }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };


}