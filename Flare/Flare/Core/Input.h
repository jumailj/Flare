#pragma once

//codelite
#include "MouseCodes.h"
#include "KeyCodes.h"

namespace Flare{
    
    class Input {
        
    public:
        static bool IsKeyPressed(KeyCode keys);
        static bool IsMouseButtonPressed(MouseCode button);
        static std::pair<float,float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}
