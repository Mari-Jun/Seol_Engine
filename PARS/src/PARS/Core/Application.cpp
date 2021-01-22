#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/Renderer.h"
#include "PARS/Core/Application.h"


namespace PARS
{
	Application::Application()
	{
		
	}
	
	Application::~Application()
	{

	}

	bool Application::Initialize()
	{
		m_Window = CreateUPtr<Window>();

		m_Renderer = CreateUPtr<Renderer>();
		bool result = m_Renderer->Initialize(m_Window->GetWindowInfo());
		if (!result)
		{
			PARS_CORE_ERROR("Could not initialize Renderer");
			return false;
		}

		return true;
	}

	void Application::ShutDown()
	{
		m_Renderer->ShutDown();
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
				m_Renderer->Run();
			}
		}
	}
}