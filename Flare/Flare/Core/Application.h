#pragma once

#include <string>  //later change it to precompiled header.
#include <memory>

#include "Window.h"

#include "../Events/Event.h"
#include "LayerStack.h"
#include "../Events/ApplicationEvent.h"



// for codelite
#include "Window.h"

namespace Flare {
    
    class Application 
    {
        public:
            Application(const std::string &name = "Flare");
            virtual ~Application();
            
            void Run();
            void Close();
            
            void OnEvent(Event& e);
            
            // return this windows
            inline Window& GetWindow() {return *m_Window;}
            // return this instance;
            inline static Application& Get() {return *s_Instance;}
            
    private:
            bool OnWindowResize(WindowResizeEvent& e);
            bool OnWindowClose(WindowCloseEvent& e);
            // actual window object;
            std::unique_ptr<Window> m_Window;
            
            bool m_Running = true;
            bool m_Minimized = false;
            
            // instance , singleton;
            LayerStack m_LayerStack;
            static Application* s_Instance;
    };
}