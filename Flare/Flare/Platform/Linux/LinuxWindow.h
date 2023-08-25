#pragma once

#include <Flare/Core/Window.h>
#include <GLFW/glfw3.h>

//codelite termperory solution
#include "../../Core/Window.h"
#include "../../../vendor/glfw/include/GLFW/glfw3.h"

namespace Flare {
    
    class LinuxWindow: public Window{
        
    public:

        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();
        
        void OnUpdate() override;
        
        inline uint32_t GetWidth() const override{ return m_Data.Width;}
        inline uint32_t GetHeight() const override{return m_Data.Height;}
        
        inline virtual void* GetNativeWindow() const {return m_Window;}
        
    private: 
        virtual void Init(const WindowProps& props);
        virtual void ShutDown();
        
        // glfw window;
        GLFWwindow* m_Window;
        
        struct WindowData {
            std::string Title;
            uint32_t Width, Height;
        };
        
        WindowData m_Data;
    };
}