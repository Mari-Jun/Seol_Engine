#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Core/Timer.h"
#include "PARS/Level/LevelManager.h"
#include "PARS/Layer/LayerManager.h"
#include "PARS/Renderer/Renderer.h"
#include "PARS/ImGui/ImGuiLayer.h"
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

		m_LevelManager = CreateUPtr<LevelManager>();

		m_LayerManager = CreateUPtr<LayerManager>();
	
		m_Renderer = CreateUPtr<Renderer>();
		result = m_Renderer->Initialize();
		if (!result)
		{
			PARS_ERROR("Could not initialize Renderer");
			return false;
		}

		//Create ImGui layer
		AddLayer(m_Renderer->CreateImGui());

		return true;
	}

	void Application::ShutDown()
	{
		m_LayerManager->Shutdown();
		m_LevelManager->Shutdown();
		m_Renderer->ShutDown();
		m_Window->Shutdown();
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

	void Application::AddLevel(const SPtr<class Level>& level)
	{
		m_LevelManager->AddLevel(level);
	}

	void Application::AddLayer(const SPtr<Layer>& layer)
	{
		m_LayerManager->AddLayer(layer);
	}

	void Application::ProcessInput()
	{
		if (Input::IsKeyFirstPressed(PARS_KEY_ESCAPE))
		{
			m_Running = false;
		}
	}

	void Application::Update()
	{
		m_Timer->Tick();
		m_Window->Update();
		m_Window->AddFpsToWindowName(m_Timer->GetFrameRate());		

		m_LevelManager->Update(m_Timer->GetDeltaTime());
		m_LayerManager->Update();
	}

	void Application::Draw()
	{	
		m_Renderer->Draw();
	}
}