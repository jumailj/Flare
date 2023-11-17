#include "LinuxWindow.h"

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
    
    
    //destructor;
    LinuxWindow::~LinuxWindow() {
            ShutDown();
    }
    
    
    void LinuxWindow::Init(const WindowProps&props){
        
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        
        
        if(!s_GLFWInitialized) 
        {
            int success = glfwInit();
            // set opengl version;
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            
            //TODO as of now it's on compat profile, it will change later.
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            
//           std::cout << glGetString(GL_VERSION)<<std::endl;
            
            if (!success) {
                LOG_WARN("glfw not init");
            }
    
            // to avoid reinit glfw.
            s_GLFWInitialized = true;
        }

       // generate window
       
       m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
       if(!m_Window){
           LOG_ERROR("window not initiated");
       }
       
       LOG_INFO("Window Created {0} [ {1}, {2} ]", props.Title, props.Width, props.Height);
       
       glfwSetWindowUserPointer(m_Window, &m_Data);
       glfwMakeContextCurrent(m_Window);
       
    
       //setting up viewport size;
       glViewport(0,0,m_Data.Width, m_Data.Height);
       
       LOG_INFO("opengl version: {0}", (const char*) glGetString(GL_VERSION) );
    }
    
    void LinuxWindow::ShutDown() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
    
    void LinuxWindow::OnUpdate(){
        
        //check if the windows is close:
        if(glfwWindowShouldClose(m_Window)){
            LOG_INFO("Window Closed!");
            ShutDown();
        }
        
         glClear(GL_COLOR_BUFFER_BIT);
         glClearColor(0.23f, 0.23f, 0.23f, 1.0f);
         
        glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
        glEnd();
        
        
        glfwSwapBuffers(m_Window);
        
        glfwPollEvents();
        
       // it's where swap buffer happens;
    }
}