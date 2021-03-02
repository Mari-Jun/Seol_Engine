#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Math/Math.h"

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
		bool IsKeyReleased(UINT key) const;
		const Vec2& GetMousePosition() const;
		const Vec2 GetRelativeMousePosition() const;

		void SetCursorHide(bool hide);
		bool IsCursorHide() const { return m_IsCursorHide; }

	public:
		friend void KeyCallback(InputManager* manager, UINT message, WPARAM key, LPARAM flags);
		friend void MouseButtonCallback(InputManager* manager, int button, int x, int y);
			
	private:
		HWND m_hwnd;
		bool m_KeyState[MAX_KEYS];
		bool m_LastKeyState[MAX_KEYS];

		Vec2 m_MouseBeforePosition;
		Vec2 m_MousePosition;

		bool m_IsCursorHide = false;
	};
}