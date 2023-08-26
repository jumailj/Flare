#include "LinuxWindow.h"

#include <Flare/Core/Log.h>

// for codelite;
#include "../../Core/Log.h"

namespace Flare{
    
    static bool s_GLFWInitialized = false;
    
    Window* Window::Create(const WindowProps& props) 
    {
        return new LinuxWindow(props);
    }
    
    LinuxWindow::LinuxWindow(const WindowProps& props) 
    {
            Init(props);
    }
    
    LinuxWindow::~LinuxWindow() {
        ShutDown();
    }
    
    
    void LinuxWindow::Init(const WindowProps&props){
        
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        
        LOG_INFO("Window Created {0} [ {1}, {2} ]", props.Title, props.Width, props.Height);
        
        
        if(!s_GLFWInitialized) 
        {
            int success = glfwInit();
            if (!success) {
                LOG_WARN("glfw not init");
            }
    
            // to avoid reinit glfw.
            s_GLFWInitialized = true;
            
        }
        
       m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
       glfwSetWindowUserPointer(m_Window, &m_Data);
       
    }
    
    void LinuxWindow::ShutDown() {
        glfwDestroyWindow(m_Window);
    }
    
    void LinuxWindow::OnUpdate(){
        glfwPollEvents();
       // it's where swap buffer happens;
    }
    
}