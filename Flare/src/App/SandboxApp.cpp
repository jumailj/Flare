#include "../Flare.h"
#include "../EntryPoint.h"

/*
 * using a derived class like 'Sandbox' instead of directly returning a new 
 * Flare::Applicaiton, instance provides a structured and flexible way to 
 * implement and extend the behavior of Application. 
*/
class Sandbox:public Flare::Application{
    /* 
     * sandbox is place where implement and customize  various things.
     * like UserInterface, Netowking, Audio...
    */
    public:
    Sandbox()
    {
        // push layer;
    }

    ~Sandbox() 
    {

    }
};

Flare::Application* Flare::CreateApplication() {
    return new Sandbox();
}