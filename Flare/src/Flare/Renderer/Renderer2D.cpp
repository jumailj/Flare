#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"

#include <Platform/OpenGL/OpenGLShader.h>
#include <Flare/Renderer/RenderCommand.h>

namespace Flare {

    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader>FlatColorShader;

    };
    
    static Renderer2DStorage* s_Data;

    void Renderer2D:: Init(){

        s_Data = new Renderer2DStorage();

        s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

        // new vertex buffer;
		Ref<VertexBuffer> squareVB;
		squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);


        // new index buffer;
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);


		s_Data->FlatColorShader = (Shader::Create("Texture.glsl"));

    }
    void Renderer2D:: ShutDown(){

        delete s_Data;

    }

    void Renderer2D:: BeginScene(const OrthographicCamera & camera){
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
         std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform",glm::mat4(1.0f));
    }

    void Renderer2D:: EndScene()
    {

    }

//primitives
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2&size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y, 0.0f}, size,color);

    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2&size, const glm::vec4& color)
    {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Flare::OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat3("u_Color", color);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

}