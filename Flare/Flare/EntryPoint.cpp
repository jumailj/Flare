
#include <Flare/Core/Application.h>
#include <Flare/Core/Log.h>
#include <GLFW/glfw3.h>

/* it's temprory solution for codelite*/
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

    Flare::Application* app  = CreateApplication();

    app->Run();
}