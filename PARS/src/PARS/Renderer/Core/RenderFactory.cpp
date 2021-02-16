#include "stdafx.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Renderer/Shader/ColorShader.h"

namespace PARS
{
	RenderFactory::RenderFactory(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
		
	}

	bool RenderFactory::Initialize()
	{
		m_RenderCompFactory = CreateUPtr<RenderComponentFactory>(m_DirectX12);
		if (!m_RenderCompFactory->Initialize())
		{
			PARS_ERROR("Could not initialize RenderComponentFactory");
			return false;
		}

		if (!CreateRootSignatures()) return false;

		CreateShaders();

		s_Instance = this;

		return true;
	}

	void RenderFactory::Shutdown()
	{
		for (auto iter = m_Shaders.begin(); iter != m_Shaders.end(); ++iter)
		{
			iter->second->Shutdown();
		}

		for (auto iter = m_RootSignatures.begin(); iter != m_RootSignatures.end(); ++iter)
		{
			if (iter->second != nullptr)
			{
				iter->second->Release();
			}
		}

		m_RenderCompFactory->Shutdown();
	}

	void RenderFactory::PrepareDraw()
	{
		m_RenderCompFactory->PrepareDraw();
	}

	void RenderFactory::Draw()
	{
		auto commandList = m_DirectX12->GetCommandList();
		commandList->SetGraphicsRootSignature(m_RootSignatures["Default"]);

		m_Shaders[ShaderType::Color]->Draw();
		m_RenderCompFactory->Draw(ShaderType::Color);
	}

	bool RenderFactory::CreateRootSignatures()
	{
		ID3D12RootSignature* defaultRootSignature = nullptr;

		D3D12_ROOT_SIGNATURE_DESC rsDesc;
		rsDesc.NumParameters = 0;
		rsDesc.pParameters = nullptr;
		rsDesc.NumStaticSamplers = 0;
		rsDesc.pStaticSamplers = nullptr;
		rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob* signatureBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		HRESULT result = D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
		
		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
		if (FAILED(result)) return false;

		auto device = m_DirectX12->GetDevice();
		device->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&defaultRootSignature));
		m_RootSignatures.insert({ "Default", defaultRootSignature });

		if (signatureBlob != nullptr)
		{
			signatureBlob->Release();
		}
		if (errorBlob != nullptr)
		{
			errorBlob->Release();
		}

		return true;
	}

	void RenderFactory::CreateShaders()
	{
		CreateShader("Default", ShaderType::Color, CreateUPtr<ColorShader>(m_DirectX12));		
	}

	void RenderFactory::CreateShader(std::string&& signatureType, ShaderType type, UPtr<Shader>&& shader)
	{
		if (m_RootSignatures[signatureType] !=nullptr && shader->Initialize(m_RootSignatures[signatureType]))
		{
			m_Shaders.insert({ type, std::move(shader) });
		}
	}

	RenderFactory* RenderFactory::s_Instance = nullptr;
}