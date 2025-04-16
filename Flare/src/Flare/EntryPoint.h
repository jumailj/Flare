#pragma once

#include "Flare/Core/Application.h"
#include "Flare/Core/Log.h"


// #define MONO_STATIC_ONLY

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>



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

                //  ---    ---   test code for Mono   ---     ---
                // mono_set_assemblies_path("Resource/mono/lib");
                // MonoDomain* domain = mono_jit_init("FlareJITRuntime");
                // if (!domain) {
                //     std::cerr << "Failed to initialize Mono runtime!" << std::endl;
                //     return -1;
                // } else {
                //     std::cout << "Mono runtime initialized successfully!" << std::endl;
                // }

                //TODO initilize Native File Dilog

                /// ---    ----   test code for v8    --     ---
    
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
