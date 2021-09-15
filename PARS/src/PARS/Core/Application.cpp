#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Core/Timer.h"
#include "PARS/Level/LevelManager.h"
#include "PARS/Layer/LayerManager.h"
#include "PARS/Renderer/Core/Renderer.h"
#include "PARS/ImGui/ImGuiLayer.h"
#include "PARS/Util/Content/AssetStore.h"
#include "PARS/Core/Application.h"

namespace PARS
{
	AppState Application::s_AppState = AppState::Active;

	Application::Application()
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
		m_Timer->OnFpsDeltaChanged([this](UINT fps) {m_Window->AddFpsToWindowName(fps); });

		m_LevelManager = CreateUPtr<LevelManager>();

		m_LayerManager = CreateUPtr<LayerManager>();

		m_AssetStore = CreateUPtr<AssetStore>();
	
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
		m_AssetStore->Shutdown();
		m_Renderer->ShutDown();
		m_Window->Shutdown();

		PARS_INFO("Good Bye");
	}

	void Application::Run()
	{
		MSG msg;

		while (GetAppState() != AppState::Dead)
		{
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else if(GetAppState() == AppState::Active)
			{
				ProcessInput();
				Update();
				Draw();
			}
		}

	}

	void Application::OpenLevel(const SPtr<class Level>& level)
	{
		m_LevelManager->OpenLevel(level);
	}

	void Application::AddLayer(const SPtr<Layer>& layer)
	{
		m_LayerManager->AddLayer(layer);
	}

	void Application::ProcessInput()
	{
		if (Input::IsKeyFirstPressed(PARS_KEY_ESCAPE))
		{
			SetAppState(AppState::Dead);
		}
		m_LevelManager->ProcessInput();
		m_LayerManager->ProcessInput();
		//m_AssetStore->ProcessInput();
	}

	void Application::Update()
	{
		m_Timer->Tick();
		m_Window->Update();

		m_LevelManager->Update(m_Timer->GetDeltaTime());
		m_LayerManager->Update();
		m_AssetStore->Update(m_Timer->GetDeltaTime());
	}

	void Application::Draw()
	{	
		m_Renderer->Draw();
	}
}