#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Input/Input.h"

namespace PARS
{
	struct WindowInfo
	{
		UINT m_Width, m_Height;
		HWND m_hwnd;
		HINSTANCE m_hInstance;

		WindowInfo(	UINT width = 1600, UINT height = 900)
			: m_Width(width), m_Height(height)
			, m_hwnd(NULL), m_hInstance(NULL)
		{
		}
	};

	class Window
	{
	public:
		Window(const std::wstring& title = L"Physics and Rendering Simulation");

		virtual ~Window() = default;

		void Initialize();
		void Shutdown();
		void Update();
		void AddFpsToWindowName(UINT fps);
		
	private:
		std::wstring m_Title;
		static WindowInfo m_WindowInfo;
		UPtr<InputManager> m_InputManager;

	public:
		const WindowInfo& GetWindowInfo() const { return m_WindowInfo; }

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	};	
}

