#pragma once

#include <string>  //later change it to precompiled header.
#include <memory>

#include "Window.h"
#include "LayerStack.h"

#include <Flare/Events/Event.h>
#include <Flare/Events/ApplicationEvent.h>
#include <Flare/ImGui/ImGuiLayer.h>

//temporary
#include <Flare/Renderer/Shader.h>
#include <Flare/Renderer/Buffer.h>
#include <Flare/Renderer/VertexArray.h>

#include <Flare/Renderer/OrthographicCamera.h>


namespace Flare {
    
    class Application 
    {
        public:
            Application(const std::string &name = "Flare");
            virtual ~Application();
            
            void Run();
            void Close();
            
            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer*layer);
            
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
            ImGuiLayer* m_ImGuiLayer;
            static Application* s_Instance; // should be private;

        
            std::shared_ptr<Shader> m_Shader;
            std::shared_ptr<VertexArray> m_VertexArray;

            std::shared_ptr<Shader> m_BlueShader;
            std::shared_ptr<VertexArray> m_SquareVA;

            OrthographicCamera m_Camera;

    };

    //to be defined in application
    Application* CreateApplication();
}