#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Input/InputManager.h"

namespace PARS
{
	InputManager* Input::s_InputManager = nullptr;

	InputManager::InputManager(HWND hwnd) : m_hwnd(hwnd)
	{
		Input::s_InputManager = this;

		memset(m_KeyState, false, sizeof(m_KeyState));
		memset(m_LastKeyState, false, sizeof(m_LastKeyState));
		memset(m_MouseButtonState, false, sizeof(m_MouseButtonState));
		memset(m_LastMouseButtonState, false, sizeof(m_LastMouseButtonState));
	}

	InputManager::~InputManager()
	{

	}

	void InputManager::Update()
	{
		memcpy_s(m_LastKeyState, sizeof(m_LastKeyState), m_KeyState, sizeof(m_KeyState));
		memcpy_s(m_LastMouseButtonState, sizeof(m_LastMouseButtonState), m_MouseButtonState, sizeof(m_MouseButtonState));

		POINT mousePos;
		GetCursorPos(&mousePos);
		m_MousePosition.first = mousePos.x, m_MousePosition.second = mousePos.y;
	}

	bool InputManager::IsKeyPressed(UINT key) const
	{
		if (key >= MAX_KEYS) return false;
		return m_KeyState[key];
	}

	bool InputManager::IsKeyFirstPressed(UINT key) const
	{
		return IsKeyPressed(key) && !m_LastKeyState[key];
	}

	bool InputManager::IsMouseClicked(UINT button) const
	{
		if (button >= MAX_BUTTONS) return false;
		return m_MouseButtonState[button];
	}

	bool InputManager::IsMouseFirstClicked(UINT button) const
	{
		return IsMouseClicked(button) && !m_LastMouseButtonState[button];
	}

	const Pos2& InputManager::GetMousePosition() const
	{
		return m_MousePosition;
	}

    void KeyCallback(InputManager* manager, UINT message, WPARAM key, LPARAM flags)
    {
        bool pressed = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
        manager->m_KeyState[key] = pressed;
    }

    void MouseButtonCallback(InputManager* manager, int button, int x, int y)
    {
        bool down = false;
        switch (button)
        {
        case WM_LBUTTONDOWN:
            SetCapture(manager->m_hwnd);
            button = PARS_MOUSE_LBUTTON;
            down = true;
            break;
        case WM_LBUTTONUP:
            ReleaseCapture();
            button = PARS_MOUSE_LBUTTON;
            down = false;
            break;
        case WM_RBUTTONDOWN:
            SetCapture(manager->m_hwnd);
            button = PARS_MOUSE_RBUTTON;
            down = true;
            break;
        case WM_RBUTTONUP:
            ReleaseCapture();
            button = PARS_MOUSE_RBUTTON;
            down = false;
            break;
        case WM_MBUTTONDOWN:
            SetCapture(manager->m_hwnd);
            button = PARS_MOUSE_MBUTTON;
            down = true;
            break;
        case WM_MBUTTONUP:
            ReleaseCapture();
            button = PARS_MOUSE_MBUTTON;
            down = false;
            break;
        }
        manager->m_MouseButtonState[button] = down;
        manager->m_MousePosition.first = x;
        manager->m_MousePosition.second = y;
    }
}