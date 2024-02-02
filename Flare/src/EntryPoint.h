#include "../../Flare/vendor/glfw/include/GLFW/glfw3.h"
#include "Core/Application.h"
#include "Core/Log.h"


/*
 * Sandbox is returning to a Application. so you can only use methods related
 * to Application
 */  

extern Flare::Application * Flare::CreateApplication();

int main(int argc, char**argv) {
    // always initilized the logger, if it's not init, logger will be null.
    Flare::Log::Init(); 

    Flare::Application* app  = Flare::CreateApplication();
    
    app->Run();
    delete app;
}