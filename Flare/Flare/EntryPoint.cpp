
#include <Flare/Core/Application.h>
#include <Flare/Core/Log.h>


#include "../Flare/Core/Application.h" //for codelite;
#include "../Flare/Core/Log.h" //for codelite;


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
    
    Flare::Log::Init(); // always inititilized the logger for futher use;
    Flare::Application* app  = CreateApplication();
    app->Run();
    
}