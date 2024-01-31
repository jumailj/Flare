

#include "../../Flare/vendor/glfw/include/GLFW/glfw3.h"
#include "Core/Application.h"
#include "Core/Log.h"


Flare::Application* CreateApplication();

/*
 * using a derived class like 'Sandbox' instead of directly returning a new 
 * Flare::Applicaiton, instance provides a structured and flexible way to 
 * implement and extend the behavior of Application. 
*/
class Sandbox: public Flare::Application {
    /* 
     * sandbox is place where implement and customize  various things.
     * like UserInterface, Netowking, Audio...
    */
public:
     Sandbox() 
    {
    }
    
    ~Sandbox()
    {
    }
};
/*
 * Sandbox is returning to a Application. so you can only use methods related
 * to Application
 */  
Flare::Application* CreateApplication() {
    return new Sandbox();
}

int main(int argc, char**argv) {
    // always initilized the logger, if it's not init, logger will be null.
    Flare::Log::Init(); 
    Flare::Application* app  = CreateApplication();
    
    app->Run();
}