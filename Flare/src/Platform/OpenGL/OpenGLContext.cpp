#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Flare/Core/Log.h>

namespace Flare{

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    :m_WindowHandle(windowHandle)
    {

    }

    void OpenGLContext::Init() {
        
        // seting current window to context. for reandering.
       glfwMakeContextCurrent(m_WindowHandle);
       int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
      
       if(!status){
        LOG_TRACE("Failed to initialize glad!");
       }else {
      
         LOG_INFO("---------OPENGL INFO---------");
         LOG_INFO("Vendor: {0},", (const char*) glGetString(GL_VENDOR));
         LOG_INFO("Renderer: {0},",(const char*) glGetString(GL_RENDERER));
         LOG_INFO("Version: {0},", (const char*) glGetString(GL_VERSION));

       }

    }

    void OpenGLContext::SwapBuffers(){
      glfwSwapBuffers(m_WindowHandle);
    }

}