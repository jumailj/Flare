#include <Flare/EntryPoint.h>
#include <Flare/Core/Flare.h>
#include <Flare/Events/Event.h>

#include <Flare/Renderer/Shader.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Flare/Renderer/Texture.h>

#include <imgui.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2d.h"

class Sandbox : public Flare::Application {
public:
    Sandbox(const Flare::ApplicationSpecification& specification)
        : Flare::Application(specification)
    {
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};

Flare::Application* Flare::CreateApplication(Flare::ApplicationCommandLineArgs args) {
    // Construct ApplicationSpecification with required arguments
    Flare::ApplicationSpecification spec("Sandbox", args);
    spec.WorkingDirectory = "./"; // give it to root dir ( may you can you Flare-editor also);
    spec.CommandLineArgs = args; // pass the command line args;
    // Pass the ApplicationSpecification object to the Sandbox constructor
    return new Sandbox(spec);
}