#include <Flare.h>
#include <Flare/Events/Event.h>
#include <imgui.h>


class ExampleLayer : public Flare::Layer {
public:
	ExampleLayer()
		:Layer("Example"), m_Camera( - 1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{

		m_VertexArray.reset(Flare::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Flare::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Flare::VertexBuffer::Create(vertices, sizeof(vertices)));
		Flare::BufferLayout layout = {
			{ Flare::ShaderDataType::Float3, "a_Position" },
			{ Flare::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Flare::IndexBuffer> indexBuffer;
		indexBuffer.reset(Flare::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Flare::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Flare::VertexBuffer> squareVB;
		squareVB.reset(Flare::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Flare::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Flare::IndexBuffer> squareIB;
		squareIB.reset(Flare::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		m_Shader.reset(new Flare::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Flare::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

	}
	// mainupdate loop;
	void OnUpdate() override {

		if (Flare::Input::IsKeyPressed( KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed;
		}
		else if (Flare::Input::IsKeyPressed(KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed;
		}

		if (Flare::Input::IsKeyPressed(KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed;
		}
		else if (Flare::Input::IsKeyPressed(KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed;
		}

		if (Flare::Input::IsKeyPressed(KEY_A)) {
			m_CameraRotation += 2.0f;
		}
		if (Flare::Input::IsKeyPressed(KEY_D)) {
			m_CameraRotation -= 2.0f;
		}


        //todo change to renderCommand
		Flare::RendereCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Flare::RendereCommand::Clear();


		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Flare::Renderer::BeginScene(m_Camera);

		Flare::Renderer::Submit(m_BlueShader, m_SquareVA);
		Flare::Renderer::Submit(m_Shader, m_VertexArray);

		Flare::Renderer::EndScene();

	}

	// graphics;
	virtual void OnImGuiRender() override {

	}

    // events;
	virtual void OnEvent(Flare::Event& event) override {

        Flare::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Flare::KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressedEvent));

	}

    bool OnKeyPressedEvent(Flare::KeyPressedEvent& event)
    {
        if(event.GetKeyCode() == KEY_X)
        {
            m_CameraPosition.x -= m_CameraSpeed;
        }   
        return true;
    }


public:
	std::shared_ptr<Flare::Shader> m_Shader;
	std::shared_ptr<Flare::VertexArray> m_VertexArray;

	std::shared_ptr<Flare::Shader> m_BlueShader;
	std::shared_ptr<Flare::VertexArray> m_SquareVA;

	Flare::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraSpeed = 0.1f;

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

        PushLayer(new ExampleLayer()); 
    }

    ~Sandbox() 
    {

    }
};

// create new application, and return new app(sandbox)
Flare::Application* Flare::CreateApplication() {
     return new Sandbox();
}
