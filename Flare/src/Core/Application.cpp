#include "Application.h"

// termprory solution for codelite
#include "Log.h"
#include "Input.h"
#include "Core.h"

#include <iostream>

//#include "../Events/ApplicationEvent.h"

namespace Flare {
    // static pointer to a instance, singleton- behavior
    Application* Application::s_Instance = nullptr;


    Application::Application(const std::string&name)
   {
       // simply points to the current Application Object.
       s_Instance = this;
       // if you didn't pass any argument. then if will used default window title, width, height.
       m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name))); // can we avoid WindowProps here.. ?TODO
       m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
       
    }
    
    Application::~Application() 
    {
        // used to clearn up the memeory.
    }

    void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


    void Application::Close(){
        m_Running = false;
    }
    
    // it's where the core of the application;
    void Application::Run(){
        
        // event checking..
//        WindowResizeEvent e(1280, 720);
//       LOG_INFO("window widht: {0}", m_Window->GetWidth());
//       LOG_INFO("window height: {0}", m_Window->GetHeight());

        bool x = Input::IsMouseButtonPressed(MOUSE_BUTTON_0);
        bool y = Input::IsKeyPressed(KEY_A);
        
        std::pair<float,float> mousePos;

        
//        LOG_INFO("mouse value = {0}", int(x));
//        LOG_INFO("key value = {0}", int(y));
        
        while(m_Running) {
            
            m_Window->OnUpdate();
            
            
            // mouse cords;
            auto [x,y] = Flare::Input::GetMousePosition();
//            LOG_INFO("{0} {1} ", x, y);
            
            // keyboard input
            /*
            if (Input::IsKeyPressed(KeyCode::A)){}
            */

            }
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