#pragma once
namespace Flare
{
	typedef enum  MouseCode
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;
}

#define MOUSE_BUTTON_0      ::Flare::Mouse::Button0
#define MOUSE_BUTTON_1      ::Flare::Mouse::Button1
#define MOUSE_BUTTON_2      ::Flare::Mouse::Button2
#define MOUSE_BUTTON_3      ::Flare::Mouse::Button3
#define MOUSE_BUTTON_4      ::Flare::Mouse::Button4
#define MOUSE_BUTTON_5      ::Flare::Mouse::Button5
#define MOUSE_BUTTON_6      ::Flare::Mouse::Button6
#define MOUSE_BUTTON_7      ::Flare::Mouse::Button7
#define MOUSE_BUTTON_LAST   ::Flare::Mouse::ButtonLast
#define MOUSE_BUTTON_LEFT   ::Flare::Mouse::ButtonLeft
#define MOUSE_BUTTON_RIGHT  ::Flare::Mouse::ButtonRight
#define MOUSE_BUTTON_MIDDLE ::Flare::Mouse::ButtonMiddle
