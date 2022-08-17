#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Renderer/Core/ResourceManager.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Renderer/Core/Renderer.h"

namespace PARS
{
	Vec4 Renderer::s_ClearColor = COLOR::Black;

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	bool Renderer::Initialize()
	{
		m_DirectX12 = CreateSPtr<DirectX12>();
		bool result = m_DirectX12->Initailize();
		if (!result)
		{
			PARS_ERROR("Could not initialize DirectX12");
			return false;
		}

		m_RenderFactory = CreateUPtr<RenderFactory>(m_DirectX12);
		result = m_RenderFactory->Initialize();
		if (!result)
		{
			PARS_ERROR("Could not initialize RenderFactory");
			return false;
		}
		
		return true;
	}

	void Renderer::ShutDown()
	{
		m_RenderFactory->Shutdown();
		m_DirectX12->ShutDown();
	}

	void Renderer::Update()
	{
		m_RenderFactory->Update();
	}

	void Renderer::Draw()
	{
		m_DirectX12->BeginScene(s_ClearColor);

		//render code
		m_RenderFactory->Draw();

		m_DirectX12->EndScene();
		m_RenderFactory->PrepareToNextDraw();
	}

	const SPtr<class ImGuiLayer>& Renderer::CreateImGui()
	{
		return m_RenderFactory->CreateImGui();
	}
}