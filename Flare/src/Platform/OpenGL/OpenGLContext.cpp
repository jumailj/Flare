#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Flare/Core/Log.h>
#include <GL/gl.h>

namespace Flare{

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    :m_WindowHandle(windowHandle)
    {

    }

    void OpenGLContext::Init() {
        
        glfwMakeContextCurrent(m_WindowHandle);
       int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
       LOG_TRACE("glad init");
       if(!status){
        LOG_TRACE("gald not init");
       }

    }

    void OpenGLContext::SwapBuffers(){
		glfwSwapBuffers(m_WindowHandle);

    }

}