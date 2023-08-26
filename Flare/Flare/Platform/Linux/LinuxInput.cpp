
#include <utility>

#include <Flare/Core/Input.h>
#include <Flare/Core/Application.h>
#include <Flare/Core/Log.h>

#include <GLFW/glfw3.h>

///codelite
#include "../../Core/Input.h"
#include "../../Core/Application.h"


namespace Flare{
    //keybaord 
    bool Input::IsKeyPressed(KeyCode key) {
        // return the current window;
       GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
       int state = glfwGetKey(window, static_cast<int32_t>(key));
       return state==GLFW_PRESS || state == GLFW_REPEAT;
    }
    
    //mouse 
    bool Input::IsMouseButtonPressed(MouseCode button){
        GLFWwindow*window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }
    
	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}
      
}