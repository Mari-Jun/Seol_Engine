#include "stdafx.h"
#include "PARS/Renderer/Core/ResourceManager.h"
#include "PARS/Renderer/Shader/Default/DefaultRootSignature.h"
#include "PARS/Renderer/Shader/Core/ShaderFactory.h"

namespace PARS
{
	ShaderFactory::ShaderFactory(const SPtr<ResourceManager>& resourceManager)
	{
		CreateRootSignatures(resourceManager);
	}

	void ShaderFactory::Initialize()
	{
		for (auto& [name, signature] : m_RootSignatures)
		{
			signature->Initialize();
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
			signature->Update();
		}
	}

	void ShaderFactory::Draw()
	{
		for (const auto& [string, signature] : m_RootSignatures)
		{
			signature->Draw();
		}

	}
	void ShaderFactory::PrepareToNextDraw()
	{
		for (const auto& [string, signature] : m_RootSignatures)
		{
			signature->PrepareToNextDraw();
		}
	}

	void ShaderFactory::CreateRootSignatures(const SPtr<ResourceManager>& resourceManager)
	{
		m_RootSignatures.insert({ "Default", CreateUPtr<DefaultRootSignature>(resourceManager) });
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
