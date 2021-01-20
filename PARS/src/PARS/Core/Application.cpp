#include "stdafx.h"
#include "PARS/Core/Application.h"
#include "PARS/Core/Window.h"

namespace PARS
{
	Application::Application()
	{
		m_Window = CreateUPtr<Window>();
	}
	
	Application::~Application()
	{

	}

	void Application::Run()
	{
		MSG msg;

		while (GetMessage(&msg, nullptr, 0, 0))
		{
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				
			}
		}
	}
}