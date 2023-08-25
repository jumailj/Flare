
#include <Flare/Core/Application.h>
#include <Flare/Core/Log.h>
#include <GLFW/glfw3.h>

#include "../Flare/Core/Application.h" //for codelite;
#include "../Flare/Core/Log.h" //for codelite;
#include "../../Flare/vendor/glfw/include/GLFW/glfw3.h" // for codelite;


Flare::Application* CreateApplication();

class Sandbox: public Flare::Application {
    
public:
     Sandbox() 
    {
                // it's where the applciaiton layers are pushed!
    }
    
    ~Sandbox()
    {
        
    }
};

Flare::Application* CreateApplication() {
    return new Sandbox();
}

int main(int argc, char**argv) {
    Flare::Log::Init(); // always initilized the logger for futher use;
    
    
     GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Flare", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
       if( glfwGetKey(window,GLFW_KEY_A)) {
           LOG_WARN("S KEY IS PRESSED");
       }
       if( glfwGetKey(window,GLFW_KEY_S)) {
           LOG_ERROR("S KEY IS PRESSED");
       }
       
       if( glfwGetKey(window,GLFW_KEY_D)) {
           LOG_INFO("D KEY IS PRESSED");
       }
       
       if( glfwGetKey(window,GLFW_KEY_W)) {
            LOG_TRACE("D KEY IS PRESSE");
       }
       
        
        /* Render here */
          glClear(GL_COLOR_BUFFER_BIT);
          
          glClearColor(0.234f, 0.23f, 0.3f, 1.0f);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
    
    Flare::Application* app  = CreateApplication();
     app->Run();
    
}