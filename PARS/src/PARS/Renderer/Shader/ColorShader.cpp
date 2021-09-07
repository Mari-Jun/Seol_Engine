#include "stdafx.h"
#include "PARS/Renderer/Shader/ColorShader.h"

namespace PARS
{
	ColorShader::ColorShader(const SPtr<DirectX12>& directX)
		: Shader(directX)
	{
		m_Type = ShaderType::Color;
	}

	void ColorShader::Shutdown()
	{
		Shader::Shutdown();
		if (m_WorldMatCB != nullptr)
		{
			m_WorldMatCB->Unmap(0, nullptr);
			m_WorldMatCB->Release();
		}
	}

	void ColorShader::Update()
	{
		UpdateShaderVariables();
	}

	void ColorShader::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, UINT newObjectCnt, UINT numOfObject)
	{
		//Mesh를 바꾸면 여기에 다시 들어오는구나..
		//근데 바꿀 때 마다 모든거를 다시 그리는 건 너무 비효율적이다.
		//따라서 어떤 방법으로 해결해야한다.

		if (m_WorldMatCB != nullptr)
		{
			m_WorldMatCB->Unmap(0, nullptr);
			m_WorldMatCB->Release();
			m_WorldMatCB = nullptr;
		}

		//이 부분도 뭔가 비효율적이다. 애초에 원래 있는 데이터를 다시 작성하는게 아니라 복사를 하는 방법은 없는 걸까?
		if (numOfObject > 0)
		{
			UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);

			m_WorldMatCB = D3DUtil::CreateBufferResource(device, commandList, nullptr, worldCBByteSize * numOfObject,
				D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

			if (FAILED(m_WorldMatCB->Map(0, nullptr, (void**)&m_WorldMatMappedData)))
			{
				PARS_ERROR("WorldMatCB Mapping Error");
			}
		}
	}

	void ColorShader::UpdateShaderVariables()
	{
		UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);

		for (int i = 0; i < m_RenderComponents.size(); ++i)
		{
			switch (m_RenderComponents[i]->GetRenderType())
			{
			case RenderType::HandMadeMesh:
				m_RenderComponents[i]->UpdateShaderVariables({
					{"CBWorld", &m_WorldMatMappedData[i * worldCBByteSize]} 
					});
				break;
			default:
				break;
			}
		}
	}

	void ColorShader::DrawRenderComp(ID3D12GraphicsCommandList* commandList, int index)
	{
		UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);
		D3D12_GPU_VIRTUAL_ADDRESS cbAddress = m_WorldMatCB->GetGPUVirtualAddress() + index * worldCBByteSize;
		commandList->SetGraphicsRootConstantBufferView(0, cbAddress);
	}


	void ColorShader::CreateShader()
	{
		m_VSBlob = CompileShader(L"Default.hlsl", "VSDiffuseMain", "vs_5_1");
		m_PSBlob = CompileShader(L"Default.hlsl", "PSDiffuseMain", "ps_5_1");
	}

	void ColorShader::CreateInputLayout()
	{
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
	}

	bool ColorShader::CreatePSO(ID3D12RootSignature* rootSignature)
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
		ZeroMemory(&psoDesc, sizeof(psoDesc));
		psoDesc.InputLayout = { m_InputLayouts.data(), (UINT)m_InputLayouts.size() };
		psoDesc.pRootSignature = rootSignature;
		psoDesc.VS = { reinterpret_cast<BYTE*>(m_VSBlob->GetBufferPointer()), m_VSBlob->GetBufferSize() };
		psoDesc.PS = { reinterpret_cast<BYTE*>(m_PSBlob->GetBufferPointer()), m_PSBlob->GetBufferSize() };
		psoDesc.RasterizerState = CreateRasterizerState();
		psoDesc.BlendState = CreateBlendState();
		psoDesc.DepthStencilState = CreateDepthStencilState();
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = m_DirectX12->IsMass4xEnable() ? 4 : 1;
		psoDesc.SampleDesc.Quality = m_DirectX12->IsMass4xEnable() ? m_DirectX12->GetMsaa4xQuality() - 1 : 0;
		psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

		HRESULT result = m_DirectX12->GetDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_PipelineState));
		if (FAILED(result)) return false;

		return true;
	}
}
