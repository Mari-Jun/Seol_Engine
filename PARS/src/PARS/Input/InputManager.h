#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
#define MAX_KEYS	256
#define MAX_BUTTONS 16

	using Pos2 = std::pair<int, int>;

	class InputManager
	{
	private:
		friend class Window;
	public:
		InputManager(HWND hwnd);
		virtual ~InputManager();

		void Update();

	public:
		bool IsKeyPressed(UINT key) const;
		bool IsKeyFirstPressed(UINT key) const;
		bool IsMouseClicked(UINT button) const;
		bool IsMouseFirstClicked(UINT button) const;
		const Pos2& GetMousePosition() const { return m_MousePosition; }

	public:
		friend void KeyCallback(InputManager* manager, UINT message, WPARAM key, LPARAM flags);
		friend void MouseButtonCallback(InputManager* manager, int button, int x, int y);
			
	private:
		HWND m_hwnd;
		bool m_KeyState[MAX_KEYS];
		bool m_LastKeyState[MAX_KEYS];

		bool m_MouseButtonState[MAX_BUTTONS];
		bool m_LastMouseButtonState[MAX_BUTTONS];
		Pos2 m_MousePosition;
	};
}