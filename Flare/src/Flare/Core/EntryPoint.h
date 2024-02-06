#pragma once
// #include "../../Flare/vendor/glfw/include/GLFW/glfw3.h"
#include "Flare/Core/Application.h"
#include "Flare/Core/Log.h"

/*
 * Sandbox is returning to a Application. so you can only use methods related
 * to Application
 */  

// Funciton Definition should be created!
extern Flare::Application * Flare::CreateApplication();

int main(int argc, char**argv) {
    // always initilized the logger, if it's not init, logger will be null.
    Flare::Log::Init(); 

    Flare::Application* app  = Flare::CreateApplication();
    
    app->Run();
    delete app;
}
