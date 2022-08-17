#include "stdafx.h"
#include "PARS/Renderer/Core/ResourceManager.h"
#include "PARS/Renderer/Shader/Core/RootSignature.h"

namespace PARS
{
	RootSignature::RootSignature(const SPtr<ResourceManager>& resourceManager)
		: m_ResourceManager(resourceManager)
		, m_DirectX12(m_ResourceManager->GetDirectX12())
	{
	}

	void RootSignature::Initialize()
	{
		CreateRootSignature(m_DirectX12->GetDevice());
		CreateShaders();
	}

	void RootSignature::Shutdown()
	{
		m_RootSignature->Release();
		for (auto& [type, shader] : m_Shaders)
		{
			shader->Shutdown();
		}
		m_Shaders.clear();
	}

	void RootSignature::Update()
	{
		const auto& device = m_DirectX12->GetDevice();
		const auto& commandList = m_DirectX12->GetCommandList();

		RenderReady(device, commandList);

		UpdateShaderVariables();

		for (const auto& [type, shader] : m_Shaders)
		{
			shader->Update(device, commandList);
		}
	}

	void RootSignature::Draw()
	{
		const auto& commandList = m_DirectX12->GetCommandList();
		commandList->SetGraphicsRootSignature(m_RootSignature);

		DrawPassFrame(commandList);
		for (const auto& [type, shader] : m_Shaders)
		{
			shader->Draw(commandList);
		}
	}

	void RootSignature::PrepareToNextDraw()
	{
	}

	void RootSignature::CreateShader(SPtr<Shader>&& shader)
	{
		if (m_RootSignature != nullptr && shader->Initialize(m_RootSignature))
		{
			m_Shaders[shader->GetShaderType()] = shader;
		}
	}
}
