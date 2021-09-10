#include "stdafx.h"
#include "PARS/Renderer/Shader/Default/DefaultRootSignature.h"
#include "PARS/Renderer/Shader/Core/ShaderFactory.h"

namespace PARS
{
	ShaderFactory::ShaderFactory(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
	}

	void ShaderFactory::Initialize()
	{
		CreateRootSignatures();

		for (auto& [name, signature] : m_RootSignatures)
		{
			signature->Initialize(m_DirectX12->GetDevice());
		}
	}

	void ShaderFactory::Shutdown()
	{
		for (auto& [name, signature] : m_RootSignatures)
		{
			signature->Shutdown();
		}
		m_RootSignatures.clear();
	}

	void ShaderFactory::Update()
	{
		for (const auto& [string, signature] : m_RootSignatures)
		{
			signature->Update(m_DirectX12->GetDevice(), m_DirectX12->GetCommandList());
		}
	}

	void ShaderFactory::Draw()
	{
		auto commandList = m_DirectX12->GetCommandList();

		for (const auto& [string, signature] : m_RootSignatures)
		{
			signature->Draw(commandList);
		}

	}
	void ShaderFactory::PrepareToNextDraw()
	{
		for (const auto& [string, signature] : m_RootSignatures)
		{
			signature->PrepareToNextDraw();
		}
	}

	void ShaderFactory::CreateRootSignatures()
	{
		m_RootSignatures.insert({ "Default", CreateUPtr<DefaultRootSignature>(m_DirectX12) });
	}

	const SPtr<Shader>& ShaderFactory::GetShader(MeshType type) const
	{
		switch (type)
		{
		case PARS::MeshType::Handmade:
			return m_RootSignatures.at("Default")->GetShaders().at(ShaderType::Color);
		case PARS::MeshType::Static:
			return m_RootSignatures.at("Default")->GetShaders().at(ShaderType::Material);
		default:
			return nullptr;
		}
	}
}
