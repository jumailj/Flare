#pragma once

#include <string>  //later change it to precompiled header.
#include <memory>

#include "Window.h"
#include "LayerStack.h"

#include <Flare/Events/Event.h>
#include <Flare/Events/ApplicationEvent.h>
#include <Flare/ImGui/ImGuiLayer.h>


namespace Flare {
    
    class Application 
    {
        public:
            Application(const std::string &name = "Flare");
            virtual ~Application();
            
            void Run();
            void Close();
            void OnShutdown();

            
            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer*layer);
            
            // return this windows
            inline Window& GetWindow() {return *m_Window;}
            // return this instance;
            inline static Application& Get() {return *s_Instance;}

            ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer;}
            
    private:
            bool OnWindowResize(WindowResizeEvent& e);
            bool OnWindowClose(WindowCloseEvent& e);

            // actual window object;
            Scope<Window> m_Window;
            
            bool m_Running = true;
            bool m_Minimized = false;
            
            // instance
            LayerStack m_LayerStack;
            ImGuiLayer* m_ImGuiLayer;

    private:
            static Application* s_Instance; // core
            float m_LastFrameTime = 0.0f;

    };

    //to be defined in application
      Application* CreateApplication(int argc, char** argv); // it will create a new Applicatio;
}