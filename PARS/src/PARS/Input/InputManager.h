#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
#define MAX_KEYS	256
#define MAX_BUTTONS 16

	class InputManager
	{
	public:
		InputManager();
		virtual ~InputManager();

		void Update();

	public:
		bool IsKeyPressed(UINT key);
		bool IsKeyPressedFirst(UINT key);
		bool IsMouseClicked(UINT button);
		bool IsMouseClickedFirst(UINT button);
		void GetMousePosition(int& x, int& y);

	public:
		void KeyCallback(UINT message, WPARAM key, LPARAM flags);
		void MouseButtonCallback(int button, int x, int y);
			
	private:
		bool m_KeyState[MAX_KEYS];
		bool m_LastKeyState[MAX_KEYS];

		bool m_MouseButtonState[MAX_BUTTONS];
		bool m_LastMouseButtonState[MAX_BUTTONS];
		int m_XPos = 0, m_YPos = 0;
	};
}