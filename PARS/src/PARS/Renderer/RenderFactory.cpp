#include "stdafx.h"
#include "PARS/Renderer/RenderFactory.h"
#include "PARS/Renderer/Shader/ColorShader.h"

namespace PARS
{
	RenderFactory::RenderFactory(SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
		
	}

	bool RenderFactory::Initialize()
	{
		auto commandQueue = m_DirectX12->GetCommandQueue();
		auto commandList = m_DirectX12->GetCommandList();
		auto commandAllocator = m_DirectX12->GetCommandAllocator();

		commandList->Reset(commandAllocator, nullptr);

		if (!CreateRootSignatures()) return false;

		CreateShaders();

		s_Instance = this;

		commandList->Close();
		ID3D12CommandList* commandLists[] = { commandList };
		commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

		m_DirectX12->WaitForGpuCompelete();

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
	}

	void RenderFactory::DrawDefualtShader()
	{
		auto commandList = m_DirectX12->GetCommandList();
		commandList->SetGraphicsRootSignature(m_RootSignatures["Default"]);
	}

	bool RenderFactory::CreateRootSignatures()
	{
		
		//매개변수가 없는 RootSignature 생성
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
		CreateShader("Default", "Color", CreateUPtr<ColorShader>(m_DirectX12));		
	}

	void RenderFactory::CreateShader(std::string&& signatureType, std::string&& shaderName, UPtr<Shader>&& shader)
	{
		if (m_RootSignatures[signatureType] !=nullptr && shader->Initialize(m_RootSignatures[signatureType]))
		{
			m_Shaders.insert({ shaderName, std::move(shader) });
		}
	}

	RenderFactory* RenderFactory::s_Instance = nullptr;
}