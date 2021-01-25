#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Input/InputManager.h"

namespace PARS
{
	InputManager* Input::s_InputManager = nullptr;

	InputManager::InputManager()
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
		m_XPos = mousePos.x, m_YPos = mousePos.y;
	}

	bool InputManager::IsKeyPressed(UINT key)
	{
		if (key >= MAX_KEYS) return false;
		return m_KeyState[key];
	}

	bool InputManager::IsMouseClicked(UINT button)
	{
		if (button >= MAX_BUTTONS) return false;
		return m_MouseButtonState[button];
	}

	void InputManager::GetMousePosition(int& x, int& y)
	{
		x = m_XPos, y = m_YPos;
	}

	void InputManager::KeyCallback(UINT message, WPARAM key, LPARAM flags)
	{
		bool pressed = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
		m_KeyState[key] = pressed;
	}

	void InputManager::MouseButtonCallback(int button, int x, int y)
	{

	}
}