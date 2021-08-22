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

		WindowInfo(UINT width = GetSystemMetrics(SM_CXSCREEN), UINT height = GetSystemMetrics(SM_CYSCREEN))
			: m_Width(width), m_Height(height)
			, m_hwnd(NULL), m_hInstance(NULL)
		{
		}

		void ChangeWindowInfo();	
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
		static UPtr<WindowInfo> s_WindowInfo;
		std::wstring m_Title;		
		UPtr<InputManager> m_InputManager;

	public:
		inline static WindowInfo* GetWindowInfo() { return s_WindowInfo.get(); }

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	};	
}

