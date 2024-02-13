#pragma once 

#include "Core.h"
#include "MouseCodes.h"
#include "KeyCodes.h"


// input will be static
namespace Flare{
    
    class Input {
        
    protected:
		Input() = default;

	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
    	//keyboard
        static bool IsKeyPressed(KeyCode key);
        // mouse
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
    }; 
}
