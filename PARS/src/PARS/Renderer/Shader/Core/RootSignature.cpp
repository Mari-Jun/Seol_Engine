#include "stdafx.h"
#include "PARS/Renderer/Shader/Core/RootSignature.h"

namespace PARS
{
	RootSignature::RootSignature(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
	}

	void RootSignature::Initialize(ID3D12Device* device)
	{
		CreateRootSignature(device);
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

	void RootSignature::Update(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		RenderReady(device, commandList);

		UpdateShaderVariables();

		for (const auto& [type, shader] : m_Shaders)
		{
			shader->Update(device, commandList);
		}
	}

	void RootSignature::Draw(ID3D12GraphicsCommandList* commandList)
	{
		commandList->SetGraphicsRootSignature(m_RootSignature);

		DrawPassFrame(commandList);
		for (const auto& [type, shader] : m_Shaders)
		{
			shader->Draw(commandList);
		}
	}
	void RootSignature::PrepareToNextDraw()
	{
		for (const auto& [type, shader] : m_Shaders)
		{
			shader->PrepareToNextDraw();
		}
	}

	void RootSignature::CreateShader(SPtr<Shader>&& shader)
	{
		if (m_RootSignature != nullptr && shader->Initialize(m_RootSignature))
		{
			m_Shaders[shader->GetShaderType()] = shader;
		}
	}
}
