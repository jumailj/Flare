#include "Application.h"

#include "Log.h"
#include "Core.h"
#include "Input.h"
#include "KeyCodes.h"
#include <Flare/Renderer/Renderer.h>


namespace Flare {
    // static pointer to a instance, singleton- behavior
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string&name)
   {
       // points to the current Application Object.
       s_Instance = this;
      
       // if you didn't pass any argument. then if will used default window (title, width, height).
       // Create New Window;
       m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
       // adding eventscallbacks
       m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
       
       //create a new imgui layer;
       m_ImGuiLayer = new ImGuiLayer();
       //pushing to layerstack
       PushOverlay(m_ImGuiLayer);

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

        float val = 0.0f;
        
        while(m_Running) {

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