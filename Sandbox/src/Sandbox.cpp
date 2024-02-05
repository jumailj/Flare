
#include <EntryPoint.h>

#include "Sandbox.h"

#include <Core/Layer.h>
#include <ImGui/ImGuiLayer.h>
#include <Core/Input.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>

#include <imgui.h>

int test = 10;

class TestLayer : public Flare::Layer{

public:

    bool keypresse = false;

    TestLayer()
    :  Layer("test layer"){

    }

    void OnUpdate() override
	{

		// if (Flare::Input::IsKeyPressed(KEY_A))
		// 	LOG_TRACE("Tab key is pressed (poll)!");

        if(Flare::Input::IsKeyPressed(KEY_A)) {
            keypresse = true;
        }else {
            keypresse = false;
        }
	}

	virtual void OnImGuiRender() override
	{
        if(keypresse){
                ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::Button("helloworld",ImVec2(20,34));
		ImGui::End();
        }
		
	}
 
    private:
};



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
       //  PushLayer(new TestLayer);
        PushLayer(new TestLayer());
       // PushLayer(new Flare::ImGuiLayer()); // i'm guil will atomatically run.
       LOG_INFO("layer added"); // no updated.
        
    }

    ~Sandbox() 
    {

    }
};

// create new application, and return new app(sandbox)
Flare::Application* Flare::CreateApplication() {
    return new Sandbox();
}
