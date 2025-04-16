#include "Application.h"
// docheckit out: https://gafferongames.com/
//#include <v8.h>
#include "Log.h"
#include "Core.h"
#include "Input.h"
#include "KeyCodes.h"
#include <Flare/Renderer/Renderer.h>

#include <GLFW/glfw3.h>

#include <Flare/Scripting/ScriptEngine.h>


// extern bool g_ApplicationRunning;
namespace Flare {
    // static pointer to a instance, singleton- behavior
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification(specification)
    {    
       // points to the current Application Object.
       s_Instance = this;


       // set the working directory: 
       if (!m_Specification.WorkingDirectory.empty())
            std::filesystem::current_path(m_Specification.WorkingDirectory); // change the dir();



       // if you didn't pass any argument. then if will used default window (title, width, height).
       // Create New Window;
       m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(m_Specification.Name)));
       
       // adding eventscallbacks | settignup all events
       m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

       // init renderer settings[]
       Renderer::Init();

       // init script engine[c#]
        ScriptEngine::Init();
       
       //create a new imgui layer and push it.
       m_ImGuiLayer = new ImGuiLayer();
       PushOverlay(m_ImGuiLayer);
    }
    
    Application::~Application() 
    {
        // used to clearn up the memeory.
        // Renderer::Shutdown();
        Renderer::Shutdown();
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

            // calculate delta time.
			float time = (float) glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

            //todo only update whne windows is mazimized, 

            for (Layer* layer: m_LayerStack) {
               layer->OnUpdate(timestep);
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

            // OnShutdown();
    }
      
    
    // applicaiton  shutdown, callback
    bool Application::OnWindowClose(WindowCloseEvent& e){
        m_Running = false;
        return true;
    }
    
    // application resize, callback
    bool Application::OnWindowResize(WindowResizeEvent& e)
	{

        //TODO fix | linux handel minimize different way.(currenlty it's not going to work.)
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {

			m_Minimized = true;
			return false;
		}
        
		m_Minimized = false;


        // when Resize event occure.. opengl recalculate the viewport;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}