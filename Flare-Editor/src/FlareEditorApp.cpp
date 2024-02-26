#include <Flare/EntryPoint.h>
#include <Flare/Core/Flare.h>
#include "EditorLayer.h"


namespace Flare{

    class FlareEditor:public Flare::Application{

        public:
        FlareEditor()
        :Application("Flare-editor")
        {
            PushLayer(new EditorLayer());
        }

        ~FlareEditor() 
        {

        }
    };

    Application* CreateApplication(int argc, char** argv) {
        return new FlareEditor();
    }

}
