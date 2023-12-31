#include "LinuxWindow.h"

#include "../../Core/Log.h"

#include "../../Events/ApplicationEvent.h"
#include "../../Events/MouseEvent.h"
#include "../../Events/KeyEvent.h"


namespace Flare{
    
    static bool s_GLFWInitialized = false;
    
    static void GLFWErrorCallback(int error, const char* description) 
	{
		LOG_ERROR("GLFW Error({0}): {1}", error, description);
	}
    
    Window* Window::Create(const WindowProps& props) {
        return new LinuxWindow(props);
    }
        
    LinuxWindow::LinuxWindow(const WindowProps& props) {
        Init(props);
    }

    LinuxWindow::~LinuxWindow() {
      Shutdown();
    } 
    void LinuxWindow::Init(const WindowProps&props){
        
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        
        if(!s_GLFWInitialized) 
        {
            // init
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
       
        //init glad
       
       m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
       if(!m_Window){
           LOG_ERROR("window not initiated");
       }
       
    
       LOG_INFO("Window Created {0} [ {1}, {2} ]", props.Title, props.Width, props.Height);
       
       // check for the gald is load or not
       
       glfwSetWindowUserPointer(m_Window, &m_Data);
       glfwMakeContextCurrent(m_Window);
       SetVSync(true);
       
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(status){
                LOG_INFO("glad init", status);
        }else {
                LOG_ERROR("glad not init!");
        }
       
                  //setting up viewport size;
       glViewport(0,0,m_Data.Width, m_Data.Height);
       
       LOG_INFO("opengl version: {0}", (const char*) glGetString(GL_VERSION) );
       
       
       // set glfw callbacks;(lam)
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);	

		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow * window) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) 
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}			
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}

			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) 
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});


		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
       
       
    }
    
    void LinuxWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
//        glfwTerminate();
    }
    
    
    void LinuxWindow::OnUpdate(){
        //check if the windows is close:
        if(glfwWindowShouldClose(m_Window)){
            LOG_INFO("Window Closed!");
            Shutdown();
        }
        
        
         glClear(GL_COLOR_BUFFER_BIT);
         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
         


        
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
        
       // it's where swap buffer happens;
    }
    
    	void LinuxWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool LinuxWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
    
}