#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Core/Timer.h"
#include "PARS/Renderer/Renderer.h"
#include "PARS/Core/Application.h"


namespace PARS
{
	Application::Application()
		: m_Running(true)
	{
		
	}
	
	Application::~Application()
	{

	}

	bool Application::Initialize()
	{
		m_Window = CreateUPtr<Window>();

		m_Timer = CreateUPtr<Timer>();
		bool result = m_Timer->Initialize();
		if (!result)
		{
			PARS_ERROR("Could not initialize Timer");
			return false;
		}
	
		m_Renderer = CreateUPtr<Renderer>();
		result = m_Renderer->Initialize(m_Window->GetWindowInfo());
		if (!result)
		{
			PARS_ERROR("Could not initialize Renderer");
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

		while (m_Running)
		{
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				ProcessInput();
				Update();
				Draw();
			}
		}
	}

	void Application::ProcessInput()
	{
		static int num = 0;
		if (Input::IsKeyPressed(PARS_KEY_UARROW))
		{
			PARS_INFO("{0}", ++num);
		}
	}

	void Application::Update()
	{
		m_Timer->Tick();

		m_Window->AddFpsToWindowName(m_Timer->GetFrameRate());
	}

	void Application::Draw()
	{
		m_Renderer->Draw();
	}
}