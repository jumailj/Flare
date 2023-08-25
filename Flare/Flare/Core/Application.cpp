
#include "Application.h"
#include <Flare/Core/Log.h>

#include "Flare/Core/Log.h" //codelite

namespace Flare {
    
    //constructor;
    Application::Application(const std::string&name) {
        LOG_ERROR("application created created");
    }
    
    // destructor;
    Application::~Application() {
        
    }
    
    void Application::Close(){
        m_Running = false;
        LOG_WARN("application exited");
    }
    
    // it's where the core of the application;
    void Application::Run(){
        
        while(m_Running) {

        //    LOG_CORE_INFO("hello wrld");

        }
    }
}