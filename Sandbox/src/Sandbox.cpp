#include <Flare/EntryPoint.h>
#include <Flare/Core/Flare.h>
#include <Flare/Events/Event.h>

#include <Flare/Renderer/Shader.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Flare/Renderer/Texture.h>

#include <imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2d.h"


class ExampleLayer : public Flare::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController(1280.0f/720.0f, true)
	{

		m_VertexArray.reset(Flare::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Flare::Ref<Flare::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Flare::VertexBuffer::Create(vertices, sizeof(vertices)));
		Flare::BufferLayout layout = {
			{ Flare::ShaderDataType::Float3, "a_Position" },
			{ Flare::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Flare::Ref<Flare::IndexBuffer> indexBuffer;
		indexBuffer.reset(Flare::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Flare::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Flare::Ref<Flare::VertexBuffer> squareVB;
		squareVB.reset(Flare::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Flare::ShaderDataType::Float3, "a_Position" },
			{ Flare::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Flare::Ref<Flare::IndexBuffer> squareIB;
		squareIB.reset(Flare::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = (Flare::Shader::Create("VertexPosColor",vertexSrc, fragmentSrc));


		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";


		m_FlatColorShader = (Flare::Shader::Create("flatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc));


		//load glsl from file, compile.
		// m_TextureShader = (Flare::Shader::Create("/home/jumail/Documents/jumail.github/Flare/bin/Debug-linux-x86_64/Sandbox/Texture.glsl"));
		auto textureShader = m_ShaderLibrary.Load("/home/jumail/Documents/jumail.github/Flare/bin/Debug-linux-x86_64/Sandbox/shaders/Texture.glsl");


		//currenlty using absolute path
		m_Texture = (Flare::Texture2D::Create("/home/jumail/Documents/jumail.github/Flare/bin/Debug-linux-x86_64/Sandbox/tik.png"));
		//m_Texture1 = (Flare::Texture2D::Create("/home/jumail/Documents/jumail.github/Flare/bin/Debug-linux-x86_64/Sandbox/jumail.png"));

		std::dynamic_pointer_cast <Flare::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast <Flare::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}
	// mainupdate loop;
	void OnUpdate(Flare::Timestep ts) override {

        // LOG_WARN("DELTA time: {0}s", ts.GetSeconds());

		m_CameraController.OnUpdate(ts);


        //todo change to renderCommand
		Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flare::RenderCommand::Clear();


		Flare::Renderer::BeginScene(m_CameraController.GetCamera());

		
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		std::dynamic_pointer_cast<Flare::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Flare::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 10; y++) {

			for (int x = 0; x < 10; x++) {

				glm::vec3 pos(x * 0.11f, y*0.11f, 0.0f);
				glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), pos) * scale;

				Flare::Renderer::Submit(m_FlatColorShader, m_SquareVA, transfrom);
			}

		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		
		m_Texture->Bind();
		Flare::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.3f)));


		// m_Texture1->Bind();
		// Flare::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.3f)));




		// Flare::Renderer::Submit(m_Shader, m_VertexArray);

		Flare::Renderer::EndScene();
	}

	// graphics;
	virtual void OnImGuiRender() override {
		
		ImGui::Begin("settigns");
		ImGui::ColorEdit3("square color:", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

    // events;
	virtual void OnEvent(Flare::Event& event) override {

		/*
			example for dispatch event;
		*/
      Flare::EventDispatcher dispatcher(event);
	  dispatcher.Dispatch<Flare::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	  
	  m_CameraController.OnEvent(event);
	  
	}

    bool OnKeyPressedEvent(Flare::KeyPressedEvent& event)
    {
        if(event.GetKeyCode() == KEY_X)
        {
         //   m_CameraPosition.x -= m_CameraSpeed;
        }   
        return false;
    }


public:
	Flare::ShaderLibrary m_ShaderLibrary;
	Flare::Ref<Flare::Shader> m_Shader;
	Flare::Ref<Flare::VertexArray> m_VertexArray;

	Flare::Ref<Flare::Shader> m_FlatColorShader;
	Flare::Ref<Flare::VertexArray> m_SquareVA;

	Flare::Ref<Flare::Texture2D> m_Texture, m_Texture1;


	Flare::OrthographicCameraController m_CameraController;



	glm::vec3 m_SquareColor = {0.45f, 0.354f, 0.783f};

};


/*
 * using a derived class like 'Sandbox' instead of directly returning a new 
 * Flare::Applicaiton, instance provides a structured and flexible way to 
 * implement and extend the behavior of Application. 
*/
class Sandbox:public Flare::Application{
    /* 
     * sandbox is place where implement and customize  various things.
     * like UserInterface, Netowking, Audio...
    */
    public:
    Sandbox()
    {

        // PushLayer(new ExampleLayer()); 
		PushLayer(new Sandbox2D());
    }

    ~Sandbox() 
    {

    }
};

// create new application, and return new app(sandbox)
Flare::Application* Flare::CreateApplication(int argc, char** argv) {
     return new Sandbox();
}
