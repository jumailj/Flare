#pragma once

//#include "../Core/Layer.h"

namespace Flare{


    class ImGuiLayer : public Layer {

    public:
         ImGuiLayer();
        ~ImGuiLayer();

          void OnAttach();
          void OnDetach();
          void OnUpdate();
          void OnEvent(Event& event);

    private:

        float m_Time;
    };

}