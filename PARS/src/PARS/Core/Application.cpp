#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Core/Timer.h"
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

		m_LayerManager = CreateUPtr<LayerManager>();
	
		m_Renderer = CreateUPtr<Renderer>(m_Window->GetWindowInfo());
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

	void Application::AddLayer(const SPtr<Layer>& layer)
	{
		m_LayerManager->AddLayer(layer);
		layer->Initialize();
	}

	void Application::ProcessInput()
	{
		static int num = 0;
		if (Input::IsKeyFirstPressed(PARS_KEY_UARROW))
		{
			static Vec3 vec1{ 1, 0, 0 };
			Quaternion q(Vec3::AxisY, Math::ToRadians(90));
			vec1.Transform(q);
			PARS_INFO(vec1);			
		}
	}

	void Application::Update()
	{
		m_Timer->Tick();
		m_Window->Update();
		m_Window->AddFpsToWindowName(m_Timer->GetFrameRate());		

		m_LayerManager->Update();
	}

	void Application::Draw()
	{	
		m_Renderer->Draw();
	}
}