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
			Mat4 m1 = { 1, 0, 0, 1, 0, 1, 0, 2, 0, 0, 1, 3, 0, 0, 0, 1 };
			Mat4 m2 = { 2,0, 0,0, 0,2,0,0, 0,0,2,0, 0,0,0,1 };
			m1 = m1 * m2;
			PARS_INFO(m1);

			m1.Invert();
			PARS_INFO(m1);

			Vec3 v1 = { 1, 2, 3 };
			Vec3 v2 = { 3, 2, 1 };
			Vec3 v3 = v1 + v2;
			PARS_INFO(v3);
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