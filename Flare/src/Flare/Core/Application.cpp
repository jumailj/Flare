#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "Core.h"

#include <Flare/Renderer/GraphicContext.h>
#include <glad/glad.h>

namespace Flare {
    // static pointer to a instance, singleton- behavior
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string&name)
   {
       // simply points to the current Application Object.
       s_Instance = this;
       // if you didn't pass any argument. then if will used default window (title, width, height).
       // Create New Window;
       m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
       m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
       
       //create a new imgui layer;
       m_ImGuiLayer = new ImGuiLayer();
       PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

        std::shared_ptr<VertexBuffer> vetexBuffer;
        vetexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices) ));
        
        BufferLayout layout= {
        {ShaderDataType::Float3, "a_Position"},
        {ShaderDataType::Float4, "a_Color"},
        };

        vetexBuffer->SetLayout(layout);  
        m_VertexArray->AddVertexBuffer(vetexBuffer);

        std::shared_ptr<IndexBuffer> indexBuffer;

		unsigned int indices[3] = {0,1,2};
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


        m_SquareVA.reset(VertexArray::Create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

        std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);





        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() 
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4( a_Position, 1.0);
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

        m_Shader.reset( new Shader(vertexSrc,fragmentSrc));


        std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
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

		m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));

    }
    
    Application::~Application() 
    {
        // used to clearn up the memeory.
    }


    // for renderer etc..
    void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}


    //eg. Imgui etc.
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


    void Application::Close(){
        m_Running = false;
    }


    void Application::OnEvent(Event& e)
	{
        // eventing loging.
        // LOG_INFO("EVENT: {0}", e.ToString());

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Flare::Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Flare::Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

    // it's where the core of the application;
    void Application::Run(){
        
        while(m_Running) {
            
            /* updall from all the layers*/
            glClearColor(0.129f, 0.14f, 0.16f, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_BlueShader->Bind();
			m_SquareVA->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);


            m_Shader->Bind();
            m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(),GL_UNSIGNED_INT , nullptr);

            for (Layer* layer: m_LayerStack) {
               layer->OnUpdate();
            }

            // later it will be on renderer thread.
            m_ImGuiLayer->Begin();
            {
                for (Layer* layer: m_LayerStack){
                    layer->OnImGuiRender();
                }
            }
            
            m_ImGuiLayer->End();
            

             m_Window->OnUpdate();
            }
    }
      
    
    bool Application::OnWindowClose(WindowCloseEvent& e){
        m_Running = false;
        return true;
    }
    
    bool Application::OnWindowResize(WindowResizeEvent& e)
	{

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {

			m_Minimized = true;
			return false;
		}
        
		m_Minimized = false;
        // todo change windows resize for opengl
		// Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
    
}