#pragma once

#include "stdafx.h"
#include "PARS/Input/InputManager.h"

namespace PARS
{
	class Input
	{
	private:
		friend InputManager;

	private:
		static InputManager* s_InputManager;

	public:
		inline static bool IsKeyPressed(UINT key) { return s_InputManager->IsKeyPressed(key); }
		inline static bool IsKeyFirstPressed(UINT key) { return s_InputManager->IsKeyFirstPressed(key); }
		inline static bool IsKeyReleased(UINT key) { return s_InputManager->IsKeyReleased(key); }
		inline static const Vec2& GetMousePosition() { return s_InputManager->GetMousePosition(); }
		inline static const Vec2 GetRelativeMousePosition() { return s_InputManager->GetRelativeMousePosition(); }

		inline static void SetCursorHide(bool hide) { s_InputManager->SetCursorHide(hide); }
		inline static bool IsCursorHide() { return s_InputManager->IsCursorHide(); }

		inline static InputManager* GetInputManager() { return s_InputManager; }
	};
}

//Key
#define PARS_MOUSE_LBUTTON		0x01
#define PARS_MOUSE_RBUTTON		0x02
#define PARS_MOUSE_MBUTTON		0x04
#define PARS_MOUSE_XBUTTON1		0x05
#define PARS_MOUSE_XBUTTON2		0x06

#define PARS_KEY_BACKSPACE		0x08
#define PARS_KEY_TAB			0x09
#define PARS_KEY_ENTER			0x0D
#define PARS_KEY_SHIFT			0x10
#define PARS_KEY_CONTROL		0x11
#define PARS_KEY_ALT			0x12
#define PARS_KEY_PAUSE			0x13
#define PARS_KEY_CAPSLOCK		0x14
#define PARS_KEY_ESCAPE			0x1B

#define PARS_KEY_SPACE			0x20
#define PARS_KEY_PAGEUP			0x21
#define PARS_KEY_PAGEDOWN		0x22
#define PARS_KEY_END			0x23
#define PARS_KEY_HOME			0x24
#define PARS_KEY_LARROW			0x25
#define PARS_KEY_UARROW			0x26
#define PARS_KEY_RARROW			0x27
#define PARS_KEY_DARROW			0x28
#define PARS_KEY_SELECT			0x29
#define PARS_KEY_PRINT			0x2A
#define PARS_KEY_EXECUTE		0x2B
#define PARS_KEY_SNAPSHOT		0x2C
#define PARS_KEY_INSERT			0x2D
#define PARS_KEY_DELETE			0x2E
#define PARS_KEY_HELP			0x2F

#define PARS_KEY_0				0x30
#define PARS_KEY_1				0x31
#define PARS_KEY_2				0x32
#define PARS_KEY_3				0x33
#define PARS_KEY_4				0x34
#define PARS_KEY_5				0x35
#define PARS_KEY_6				0x36
#define PARS_KEY_7				0x37
#define PARS_KEY_8				0x38
#define PARS_KEY_9				0x39

#define PARS_KEY_A				0x41
#define PARS_KEY_B				0x42
#define PARS_KEY_C				0x43
#define PARS_KEY_D				0x44
#define PARS_KEY_E				0x45
#define PARS_KEY_F				0x46
#define PARS_KEY_G				0x47
#define PARS_KEY_H				0x48
#define PARS_KEY_I				0x49
#define PARS_KEY_J				0x4A
#define PARS_KEY_K				0x4B
#define PARS_KEY_L				0x4C
#define PARS_KEY_M				0x4D
#define PARS_KEY_N				0x4E
#define PARS_KEY_O				0x4F
#define PARS_KEY_P				0x50
#define PARS_KEY_Q				0x51
#define PARS_KEY_R				0x52
#define PARS_KEY_S				0x53
#define PARS_KEY_T				0x54
#define PARS_KEY_U				0x55
#define PARS_KEY_V				0x56
#define PARS_KEY_W				0x57
#define PARS_KEY_X				0x58
#define PARS_KEY_Y				0x59
#define PARS_KEY_Z				0x5A

#define PARS_KEY_NUMPAD0		0x60
#define PARS_KEY_NUMPAD1		0x61
#define PARS_KEY_NUMPAD2		0x62
#define PARS_KEY_NUMPAD3		0x63
#define PARS_KEY_NUMPAD4		0x64
#define PARS_KEY_NUMPAD5		0x65
#define PARS_KEY_NUMPAD6		0x66
#define PARS_KEY_NUMPAD7		0x67
#define PARS_KEY_NUMPAD8		0x68
#define PARS_KEY_NUMPAD9		0x69
#define PARS_KEY_MULTIPLY		0x6A
#define PARS_KEY_ADD			0x6B
#define PARS_KEY_SEPARATOR		0x6C
#define PARS_KEY_SUBTRACT		0x6D
#define PARS_KEY_DECIMAL		0x6E
#define PARS_KEY_DIVIDE			0x6F
#define PARS_KEY_F1				0x70
#define PARS_KEY_F2				0x71
#define PARS_KEY_F3				0x72
#define PARS_KEY_F4				0x73
#define PARS_KEY_F5				0x74
#define PARS_KEY_F6				0x75
#define PARS_KEY_F7				0x76
#define PARS_KEY_F8				0x77
#define PARS_KEY_F9				0x78
#define PARS_KEY_F10			0x79
#define PARS_KEY_F11			0x7A
#define PARS_KEY_F12			0x7B