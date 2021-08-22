#include "stdafx.h"
#include "PARS/Renderer/Core/Viewport.h"
#include "PARS/Core/Window.h"

namespace PARS
{
	void Viewport::SetLeft(float left)
	{
		RECT rect;
		GetWindowRect(Window::GetWindowInfo()->m_hwnd, &rect);
		POINT point = { static_cast<LONG>(left), 0 };
		ScreenToClient(Window::GetWindowInfo()->m_hwnd, &point);

		if (point.x != m_Left)
		{
			m_Left = static_cast<float>(point.x);
			m_IsChangeViewport = true;
		}
	}

	void Viewport::SetTop(float top)
	{
		RECT rect;
		GetWindowRect(Window::GetWindowInfo()->m_hwnd, &rect);
		POINT point = { 0, static_cast<LONG>(top) };
		ScreenToClient(Window::GetWindowInfo()->m_hwnd, &point);

		if (point.y != m_Top)
		{
			m_Top = static_cast<float>(point.y);
			m_IsChangeViewport = true;
		}
	}

	void Viewport::SetWidth(float width)
	{
		if (width != m_Width)
		{
			m_Width = width;
			m_IsChangeViewport = true;
		}
	}

	void Viewport::SetHeight(float height)
	{
		if (height != m_Height)
		{
			m_Height = height;
			m_IsChangeViewport = true;
		}
	}
}
