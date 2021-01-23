#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	struct WindowInfo
	{
		std::wstring m_Title;
		UINT m_Width, m_Height;
		HWND m_hwnd;
		HINSTANCE m_hInstance;

		WindowInfo(const std::wstring& title = L"Physics and Rendering Simulation",
			UINT width = 1280, UINT height = 720)
			: m_Title(title), m_Width(width), m_Height(height)
			, m_hwnd(NULL), m_hInstance(NULL)
		{
		}
	};

	class Window
	{
	public:
		Window();

		virtual ~Window() = default;

		void Initialize();
		void AddFpsToWindowName(UINT fps);
		
	private:
		WindowInfo m_WindowInfo;

	public:
		const WindowInfo& GetWindowInfo() const { return m_WindowInfo; }
	};


	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
}

