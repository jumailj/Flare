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
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      
 

            
            if (success) {
                LOG_INFO("glfw init");
            }else {
                LOG_ERROR("glfw not init!");
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
       
       // check for the gald is load or not
       
       glfwSetWindowUserPointer(m_Window, &m_Data);
       glfwMakeContextCurrent(m_Window);
       
       //init glad
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(status){
                LOG_INFO("glad init", status);
        }else {
                LOG_ERROR("glad not init!");
        }

    
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
         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
         
//        glBegin(GL_POLYGON);
//        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
//        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
//        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
//        glEnd();
        
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
        
       // it's where swap buffer happens;
    }
}