#include <Flare/Renderer/Buffer.h>


namespace Flare{

    class OpenGLVertexBuffer: public VertexBuffer 
    {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(float * vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;
        virtual void SetData(const void* data, uint32_t size) override;

        virtual const BufferLayout& GetLayout() const override {
            return m_Layout;
        }
        virtual void SetLayout(const BufferLayout& layout) override {
            m_Layout = layout;
        }

    private:
        uint32_t m_RenderID;
        BufferLayout m_Layout;


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