#pragma once

#include <string>  //later change it to precompiled header.
#include <memory>

#include <Flare/Core/Window.h>

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
            
            // return this windows
            inline Window& GetWindow() {return *m_Window;}
            
            // return this instance;
            inline static Application& Get() {return *s_Instance;}
            
    private:
            // actual window object;
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
            
            // instance , singleton;
            static Application* s_Instance;
    };

}