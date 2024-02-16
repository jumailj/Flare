#pragma once
#include <Flare/Core/Flare.h>

class Sandbox2D : public Flare::Layer{

    //todo fix acpect ration when changing camera aspect ratio.
    public:
    Sandbox2D() 
    : Layer("sandbox2d"), m_CameraController(1280.0f/720.0f, true)
    {


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


	}
	// mainupdate loop;
	void OnUpdate(Flare::Timestep ts) override {

        // LOG_WARN("DELTA time: {0}s", ts.GetSeconds());

		m_CameraController.OnUpdate(ts);


        //todo change to renderCommand
		Flare::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flare::RenderCommand::Clear();


		Flare::Renderer::BeginScene(m_CameraController.GetCamera());

		
		std::dynamic_pointer_cast<Flare::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Flare::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
                glm::vec3 pos (0.0f, 0.0f, 0.0f);
				glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), pos) * scale;

				Flare::Renderer::Submit(m_FlatColorShader, m_SquareVA, transfrom);


		
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

        // example for 
      Flare::EventDispatcher dispatcher(event);
	  dispatcher.Dispatch<Flare::KeyPressedEvent>(BIND_EVENT_FN(Sandbox2D::OnKeyPressedEvent));
	  
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


	Flare::Ref<Flare::Shader> m_FlatColorShader;
	Flare::Ref<Flare::VertexArray> m_SquareVA;

	Flare::Ref<Flare::Texture2D> m_Texture, m_Texture1;


	Flare::OrthographicCameraController m_CameraController;



	glm::vec3 m_SquareColor = {0.45f, 0.354f, 0.783f};

};