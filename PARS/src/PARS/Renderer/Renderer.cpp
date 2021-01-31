#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/ImGui/ImGuiLayer.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Renderer/Renderer.h"

namespace PARS
{
	Renderer::Renderer(const WindowInfo& info)
		: m_WindowInfo(info)
	{
	}

	Renderer::~Renderer()
	{
	}

	bool Renderer::Initialize()
	{
		m_DirectX12 = CreateSPtr<DirectX12>(m_WindowInfo);
		bool result = m_DirectX12->Initailize();
		if (!result)
		{
			PARS_ERROR("Could not initialize DirectX12");
			return false;
		}
		
		return true;
	}
	void Renderer::ShutDown()
	{
		m_ImGuiLayer->Shutdown();
		m_ImGuiLayer.reset();
		m_DirectX12->ShutDown();
	}

	void Renderer::Draw()
	{
		m_DirectX12->BeginScene();

		//render code
		m_ImGuiLayer->Draw();

		m_DirectX12->EndScene();
	}

	const SPtr<ImGuiLayer>& Renderer::CreateImGui()
	{
		m_ImGuiLayer = CreateSPtr<ImGuiLayer>(m_WindowInfo);
		return m_ImGuiLayer;
	}
}