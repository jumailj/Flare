#pragma once 

#include <glm/glm.hpp>


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
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
    }; 
}
