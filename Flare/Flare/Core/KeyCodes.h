#pragma once

namespace Flare
{
	 typedef enum KeyCode
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	}Keys;
}

// From glfw3.h
#define KEY_SPACE           ::Flare::Keys::Space
#define KEY_APOSTROPHE      ::Flare::Keys::Apostrophe    /* ' */
#define KEY_COMMA           ::Flare::Keys::Comma         /* , */
#define KEY_MINUS           ::Flare::Keys::Minus         /* - */
#define KEY_PERIOD          ::Flare::Keys::Period        /* . */
#define KEY_SLASH           ::Flare::Keys::Slash         /* / */
#define KEY_0               ::Flare::Keys::D0
#define KEY_1               ::Flare::Keys::D1
#define KEY_2               ::Flare::Keys::D2
#define KEY_3               ::Flare::Keys::D3
#define KEY_4               ::Flare::Keys::D4
#define KEY_5               ::Flare::Keys::D5
#define KEY_6               ::Flare::Keys::D6
#define KEY_7               ::Flare::Keys::D7
#define KEY_8               ::Flare::Keys::D8
#define KEY_9               ::Flare::Keys::D9
#define KEY_SEMICOLON       ::Flare::Keys::Semicolon     /* ; */
#define KEY_EQUAL           ::Flare::Keys::Equal         /* = */
#define KEY_A               ::Flare::Keys::A
#define KEY_B               ::Flare::Keys::B
#define KEY_C               ::Flare::Keys::C
#define KEY_D               ::Flare::Keys::D
#define KEY_E               ::Flare::Keys::E
#define KEY_F               ::Flare::Keys::F
#define KEY_G               ::Flare::Keys::G
#define KEY_H               ::Flare::Keys::H
#define KEY_I               ::Flare::Keys::I
#define KEY_J               ::Flare::Keys::J
#define KEY_K               ::Flare::Keys::K
#define KEY_L               ::Flare::Keys::L
#define KEY_M               ::Flare::Keys::M
#define KEY_N               ::Flare::Keys::N
#define KEY_O               ::Flare::Keys::O
#define KEY_P               ::Flare::Keys::P
#define KEY_Q               ::Flare::Keys::Q
#define KEY_R               ::Flare::Keys::R
#define KEY_S               ::Flare::Keys::S
#define KEY_T               ::Flare::Keys::T
#define KEY_U               ::Flare::Keys::U
#define KEY_V               ::Flare::Keys::V
#define KEY_W               ::Flare::Keys::W
#define KEY_X               ::Flare::Keys::X
#define KEY_Y               ::Flare::Keys::Y
#define KEY_Z               ::Flare::Keys::Z
#define KEY_LEFT_BRACKET    ::Flare::Keys::LeftBracket   /* [ */
#define KEY_BACKSLASH       ::Flare::Keys::Backslash     /* \ */
#define KEY_RIGHT_BRACKET   ::Flare::Keys::RightBracket  /* ] */
#define KEY_GRAVE_ACCENT    ::Flare::Keys::GraveAccent   /* ` */
#define KEY_WORLD_1         ::Flare::Keys::World1        /* non-US #1 */
#define KEY_WORLD_2         ::Flare::Keys::World2        /* non-US #2 */

///* Function keys */
#define KEY_ESCAPE          ::Flare::Keys::Escape
#define KEY_ENTER           ::Flare::Keys::Enter
#define KEY_TAB             ::Flare::Keys::Tab
#define KEY_BACKSPACE       ::Flare::Keys::Backspace
#define KEY_INSERT          ::Flare::Keys::Insert
#define KEY_DELETE          ::Flare::Keys::Delete
#define KEY_RIGHT           ::Flare::Keys::Right
#define KEY_LEFT            ::Flare::Keys::Left
#define KEY_DOWN            ::Flare::Keys::Down
#define KEY_UP              ::Flare::Keys::Up
#define PAGE_UP         ::Flare::Keys::PageUp
#define KEY_PAGE_DOWN       ::Flare::Keys::PageDown
#define KEY_HOME            ::Flare::Keys::Home
#define KEY_END             ::Flare::Keys::End
#define KEY_CAPS_LOCK       ::Flare::Keys::CapsLock
#define KEY_SCROLL_LOCK     ::Flare::Keys::ScrollLock
#define KEY_NUM_LOCK        ::Flare::Keys::NumLock
#define KEY_PRINT_SCREEN    ::Flare::Keys::PrintScreen
#define KEY_PAUSE           ::Flare::Keys::Pause
#define KEY_F1              ::Flare::Keys::F1
#define KEY_F2              ::Flare::Keys::F2
#define KEY_F3              ::Flare::Keys::F3
#define KEY_F4              ::Flare::Keys::F4
#define KEY_F5              ::Flare::Keys::F5
#define KEY_F6              ::Flare::Keys::F6
#define KEY_F7              ::Flare::Keys::F7
#define KEY_F8              ::Flare::Keys::F8
#define KEY_F9              ::Flare::Keys::F9
#define KEY_F10             ::Flare::Keys::F10
#define KEY_F11             ::Flare::Keys::F11
#define KEY_F12             ::Flare::Keys::F12
#define KEY_F13             ::Flare::Keys::F13
#define KEY_F14             ::Flare::Keys::F14
#define KEY_F15             ::Flare::Keys::F15
#define KEY_F16             ::Flare::Keys::F16
#define KEY_F17             ::Flare::Keys::F17
#define KEY_F18             ::Flare::Keys::F18
#define KEY_F19             ::Flare::Keys::F19
#define KEY_F20             ::Flare::Keys::F20
#define KEY_F21             ::Flare::Keys::F21
#define KEY_F22             ::Flare::Keys::F22
#define KEY_F23             ::Flare::Keys::F23
#define KEY_F24             ::Flare::Keys::F24
#define KEY_F25             ::Flare::Keys::F25

///* Keypad */
#define KEY_KP_0            ::Flare::Keys::KP0
#define KEY_KP_1            ::Flare::Keys::KP1
#define KEY_KP_2            ::Flare::Keys::KP2
#define KEY_KP_3            ::Flare::Keys::KP3
#define KEY_KP_4            ::Flare::Keys::KP4
#define KEY_KP_5            ::Flare::Keys::KP5
#define KEY_KP_6            ::Flare::Keys::KP6
#define KEY_KP_7            ::Flare::Keys::KP7
#define KEY_KP_8            ::Flare::Keys::KP8
#define KEY_KP_9            ::Flare::Keys::KP9
#define KEY_KP_DECIMAL      ::Flare::Keys::KPDecimal
#define KEY_KP_DIVIDE       ::Flare::Keys::KPDivide
#define KEY_KP_MULTIPLY     ::Flare::Keys::KPMultiply
#define KEY_KP_SUBTRACT     ::Flare::Keys::KPSubtract
#define KEY_KP_ADD          ::Flare::Keys::KPAdd
#define KEY_KP_ENTER        ::Flare::Keys::KPEnter
#define KEY_KP_EQUAL        ::Flare::Keys::KPEqual

#define KEY_LEFT_SHIFT      ::Flare::Keys::LeftShift
#define KEY_LEFT_CONTROL    ::Flare::Keys::LeftControl
#define KEY_LEFT_ALT        ::Flare::Keys::LeftAlt
#define KEY_LEFT_SUPER      ::Flare::Keys::LeftSuper
#define KEY_RIGHT_SHIFT     ::Flare::Keys::RightShift
#define KEY_RIGHT_CONTROL   ::Flare::Keys::RightControl
#define KEY_RIGHT_ALT       ::Flare::Keys::RightAlt
#define KEY_RIGHT_SUPER     ::Flare::Keys::RightSuper
#define KEY_MENU            ::Flare::Keys::Menu



