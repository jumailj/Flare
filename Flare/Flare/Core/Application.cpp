
#include "Application.h"
#include <Flare/Core/Log.h>


// termprory solution for codelite
#include "Flare/Core/Log.h" //codelite

namespace Flare {
    
    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string&name)
   {
       s_Instance = this;
       m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
    }
    

    Application::~Application() {
        
    }
    
    void Application::Close(){
        m_Running = false;
        LOG_WARN("application exited");
    }
    
    // it's where the core of the application;
    void Application::Run(){
        
        while(m_Running) {

         //   LOG_TRACE("in Loop");
            
            m_Window->OnUpdate();

        }
    }
}