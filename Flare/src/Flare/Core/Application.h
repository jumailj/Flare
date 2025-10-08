#pragma once

#include <string>  //later change it to precompiled header.
#include <memory>

#include "Window.h"
#include "LayerStack.h"

#include <Flare/Events/Event.h>
#include <Flare/Events/ApplicationEvent.h>
#include <Flare/ImGui/ImGuiLayer.h>


namespace Flare {

    struct ApplicationCommandLineArgs{

        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int index) const
        {
                // check if the index is < count, then assert;
                return Args[index];
        }
    };

    // this is the application specification;
    struct ApplicationSpecification
    {
        std::string Name = "Flare Application";
        std::string WorkingDirectory;
        ApplicationCommandLineArgs CommandLineArgs;

        ApplicationSpecification(const std::string& name, const ApplicationCommandLineArgs& args)
        : Name(name), CommandLineArgs(args) {}

    };


    
    class Application 
    {
        public:
            // Application(const std::string& name = "Flare App", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
            Application(const ApplicationSpecification& specification);
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

            ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer;}

            // ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

            const ApplicationSpecification& GetSpecification() const {return m_Specification;}
            
    private:
            ApplicationSpecification m_Specification;
            // ApplicationCommandLineArgs m_CommandLineArgs;

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

            // friend int ::main(int argc, char** argv);

    };

    //to be defined in application
      Application* CreateApplication(ApplicationCommandLineArgs args); // it will create a new Applicatio;
}