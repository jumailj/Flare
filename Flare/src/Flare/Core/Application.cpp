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



    // VERTEX ARRAY
    // INDEX  BUFFER

        glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = {
			0,1,2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;
            void main() 
            {
                v_Position = a_Position;
                gl_Position = vec4( a_Position, 1.0);
            }
        )";


        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            void main() 
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";



        m_Shader.reset( new Shader(vertexSrc,fragmentSrc));
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
            glClearColor(0.10f, .01f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();

            glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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