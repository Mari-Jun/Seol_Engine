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
	}

	InputManager::~InputManager()
	{

	}

	void InputManager::Update()
	{
     	memcpy_s(m_LastKeyState, sizeof(m_LastKeyState), m_KeyState, sizeof(m_KeyState));
       
        if (m_IsCursorHide)
        {
            RECT rect;
            GetWindowRect(m_hwnd, &rect);
            POINT point = { static_cast<int>(m_MouseBeforePosition.x), static_cast<int>(m_MouseBeforePosition.y) };
          
            ClientToScreen(m_hwnd, &point);

            SetCursorPos(point.x, point.y);
            m_MousePosition = m_MouseBeforePosition;
        }
        else
        {
            m_MouseBeforePosition = m_MousePosition;
        }
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

    bool InputManager::IsKeyReleased(UINT key) const
    {
        if (key >= MAX_KEYS) return false;
        return !m_KeyState[key] && m_LastKeyState[key];
    }

    const Vec2& InputManager::GetMousePosition() const
    {
        return m_MousePosition;
    }

    const Vec2 InputManager::GetRelativeMousePosition() const
    {
        return { m_MousePosition - m_MouseBeforePosition };
    }

    void InputManager::SetCursorHide(bool hide)
    {
        if (hide)
        {
            m_MouseBeforePosition = m_MousePosition;
        }
        m_IsCursorHide = hide;
        ShowCursor(!hide);
    }

    void KeyCallback(InputManager* manager, UINT message, WPARAM key, LPARAM flags)
    {
        bool pressed = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
        manager->m_KeyState[key] = pressed;
    }

    void MouseButtonCallback(InputManager* manager, int button, WPARAM wParam, int x, int y)
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
        case WM_XBUTTONDOWN:
            SetCapture(manager->m_hwnd);
            if (GET_KEYSTATE_WPARAM(wParam) == MK_XBUTTON1)
                button = PARS_MOUSE_XBUTTON1;
            else if (GET_KEYSTATE_WPARAM(wParam) == MK_XBUTTON2)
                button = PARS_MOUSE_XBUTTON2;
            down = true;
            break;
        case WM_XBUTTONUP:
            ReleaseCapture();
            if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
                button = PARS_MOUSE_XBUTTON1;
            else if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2)
                button = PARS_MOUSE_XBUTTON2;
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
        case WM_MOUSEMOVE:
        {
            auto& position = manager->m_MousePosition;
            if (position.x != x)
            {
                position.x = static_cast<float>(x);
                manager->m_KeyState[PARS_MOUSE_XMOVE] = true;
            }
            if (position.y != y)
            {
                position.y = static_cast<float>(y);
                manager->m_KeyState[PARS_MOUSE_YMOVE] = true;
            }
            break;
        }
        }

        manager->m_KeyState[button] = down;

    }
}