#pragma once

#include "Flare/Core/Application.h"
#include "Flare/Core/Log.h"

/*
 * Sandbox is returning to a Application. so you can only use methods related
 * to Application
 */  

// Funciton Definition should be created!
extern Flare::Application * Flare::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace Flare{

    int Main(int argc, char** argv)
    {
        while(g_ApplicationRunning) 
        {
            // inittilize Logger sigleton
            Flare::Log::Init();
            
            // create new app
            Flare::Application * app = CreateApplication(argc, argv);
            if(!app){LOG_ERROR("Client Application NULL");}

            app->Run();

            delete app;
            Log::Shutdown();
            
        }
        // return 0 if applciation not started;
        return 0;

    }
}

int main(int argc, char**argv) {
    return Flare::Main(argc,argv);
}
