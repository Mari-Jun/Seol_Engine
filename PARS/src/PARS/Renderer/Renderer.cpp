#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Renderer/Renderer.h"

namespace PARS
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	bool Renderer::Initialize(const WindowInfo& info)
	{
		m_DirectX12 = CreateUPtr<DirectX12>(info);
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
		m_DirectX12->ShutDown();
	}

	void Renderer::Run()
	{
		m_DirectX12->BeginScene();

		//render code
		Draw();
		
		m_DirectX12->EndScene();
	}

	bool Renderer::Draw()
	{
		return true;
	}
}