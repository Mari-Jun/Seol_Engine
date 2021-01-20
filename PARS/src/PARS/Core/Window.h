#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class Window
	{
	public:
		Window(const std::wstring& title = L"Physics and Rendering Simulation",
			UINT width = 1280, UINT height = 720);

		virtual ~Window() = default;

		void Initialize();
		
	private:
		std::wstring m_Title;
		UINT m_Width, m_Height;
		HWND m_hwnd;
		HINSTANCE m_hInstance;

	public:
		HINSTANCE GetHInstance() const { return m_hInstance; }
	};


	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
}

