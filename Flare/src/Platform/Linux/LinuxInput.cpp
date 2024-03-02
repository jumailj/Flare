
#include <utility>

#include <Flare/Core/Input.h>
#include <Flare/Core/Application.h>
#include <GLFW/glfw3.h>

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
        // return the current windows;
		GLFWwindow*window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }
    // current mouse-pos
	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	// mouse -x
	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	// mouse -y
	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
      
}