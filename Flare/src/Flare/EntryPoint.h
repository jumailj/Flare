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
extern Flare::Application * Flare::CreateApplication(ApplicationCommandLineArgs args);

// entry.
int main(int argc, char**argv) {

                // initilize Logger sigleton
                Flare::Log::Init();

                //TODO initilize Native File Dilog
    
                // // cheking for v8
                //   v8::V8::InitializeICUDefaultLocation(argv[0]);
                //   v8::V8::InitializeExternalStartupData(argv[0]);
    
                //   std::unique_ptr<v8::Platform> platfrom = v8::platform::NewDefaultPlatform();
                // //   LOG_INFO("platfrom: {0}", platfrom.get());
    
                //   std::cout<< platfrom.get() <<std::endl;
                //   v8::V8::InitializePlatform(platfrom.get());
                //   v8::V8::Initialize();
    
    
                // create new app, it's extern,definition should be created on client.
                Flare::Application * app = Flare::CreateApplication({ argc, argv });
                if(!app){LOG_ERROR("Client Application NULL");}
    
                app->Run();
    
                delete app;
                // uninitilize Logger.
                Flare::Log::Shutdown();

    // return Flare::Main(argc,argv);
}
