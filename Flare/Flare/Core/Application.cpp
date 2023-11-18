
#include "Application.h"

// termprory solution for codelite
#include "Log.h"
#include "Input.h"

namespace Flare {
    // static pointer to a instance, singleton- behavior
    Application* Application::s_Instance = nullptr;


    Application::Application(const std::string&name)
   {
       // simply points to the current Application Object.
       s_Instance = this;
       // if you didn't pass any argument. then if will used default window title, width, height.
       m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
    }
    
    Application::~Application() 
    {
        // used to clearn up the memeory.
    }
    
    void Application::Close(){
        m_Running = false;
    }
    
    // it's where the core of the application;
    void Application::Run(){
        
//       LOG_INFO("window widht: {0}", m_Window->GetWidth());
//       LOG_INFO("window height: {0}", m_Window->GetHeight());



        bool x = Input::IsMouseButtonPressed(MOUSE_BUTTON_0);
        bool y = Input::IsKeyPressed(KEY_A);
        
        std::pair<float,float> mousePos;
 
        
//        LOG_INFO("mouse value = {0}", int(x));
//        LOG_INFO("key value = {0}", int(y));
        
        while(m_Running) {
            m_Window->OnUpdate();
            
            //test;
          //  mousePos =  Input::GetMousePosition();
          //  LOG_ERROR("x {0} y {0}", (int)mousePos.first, (int)mousePos.second);
            
            // test;
           // if(Input::IsKeyPressed(KEY_A)){
           //     LOG_WARN("a key presed");
           //  }
            
            // test;
         //    if(Input::IsMouseButtonPressed(MOUSE_BUTTON_0)){
          //      LOG_WARN("left mouse button pressed!");
            }
    }
    
}