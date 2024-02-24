#pragma once

#include "Flare/Core/Application.h"
#include "Flare/Core/Log.h"

// #include <v8.h>
// #include <libplatform/libplatform.h>

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
            // initilize Logger sigleton
            Flare::Log::Init();

            // // cheking for v8
            //   v8::V8::InitializeICUDefaultLocation(argv[0]);
            //   v8::V8::InitializeExternalStartupData(argv[0]);

            //   std::unique_ptr<v8::Platform> platfrom = v8::platform::NewDefaultPlatform();
            // //   LOG_INFO("platfrom: {0}", platfrom.get());

            //   std::cout<< platfrom.get() <<std::endl;
            //   v8::V8::InitializePlatform(platfrom.get());
            //   v8::V8::Initialize();


            // create new app, it's extern,definition should be created on client.
            Flare::Application * app = CreateApplication(argc, argv);
            if(!app){LOG_ERROR("Client Application NULL");}

            app->Run();

            delete app;
            // uninitilize Logger.
            Flare::Log::Shutdown();
            
        }
        // return 0 if applciation not started;
        return 0;

    }
}
// entry.
int main(int argc, char**argv) {
    return Flare::Main(argc,argv);
}
