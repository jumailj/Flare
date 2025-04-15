#include <Flare/EntryPoint.h>
#include <Flare/Core/Flare.h>
#include "EditorLayer.h"

namespace Flare {

    class FlareEditor : public Application {

    public:
        FlareEditor(ApplicationCommandLineArgs args)
            : Application(ApplicationSpecification{ "Flare Editor", args }) // Pass ApplicationSpecification
        {
            PushLayer(new EditorLayer());
        }

        ~FlareEditor() 
        {
        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        return new FlareEditor(args);
    }

}