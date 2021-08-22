#include "stdafx.h"
#include "PARS/Renderer/Shader/ColorShader.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	ColorShader::ColorShader(const SPtr<DirectX12>& directX)
		: Shader(directX)
	{
	}

	void ColorShader::Shutdown()
	{
		Shader::Shutdown();
		if (m_ColorPassCB != nullptr)
		{
			m_ColorPassCB->Unmap(0, nullptr);
			m_ColorPassCB->Release();
		}
		if (m_WorldMatCB != nullptr)
		{
			m_WorldMatCB->Unmap(0, nullptr);
			m_WorldMatCB->Release();
		}
	}

	void ColorShader::UpdateShaderVariables(ID3D12GraphicsCommandList* commandList, const std::vector<SPtr<RenderComponent>>& renderComps, const CBColorPass& cbPass)
	{
		//이동된 객체만 Update해야한다.
		UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);
		for (int i = 0; i < renderComps.size(); ++i)
		{
			const auto& owner = renderComps[i]->GetOwner().lock();
			if (owner->IsChangedWorldMatrix())
			{
				owner->ResetChangedWorldMatrix();

				CBWorldMat mappedWorldMat;
				Mat4 worldMatrix = owner->GetWorldMatrix();
				Mat4 worldInverseTranspose = worldMatrix;
				worldMatrix.Transpose();
				worldInverseTranspose.Invert();
				mappedWorldMat.m_WorldMatrix = worldMatrix;
				mappedWorldMat.m_WorldInverseTranspose = worldInverseTranspose;

				memcpy(&m_WorldMatMappedData[i * worldCBByteSize], &mappedWorldMat, sizeof(CBWorldMat));
			}
		}

		memcpy(m_ColorPassMappedData, &cbPass, sizeof(CBColorPass));
	}

	void ColorShader::DrawRenderComp(ID3D12GraphicsCommandList* commandList, const SPtr<RenderComponent>& renderComp, int index)
	{
		UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);
		D3D12_GPU_VIRTUAL_ADDRESS cbAddress = m_WorldMatCB->GetGPUVirtualAddress() + index * worldCBByteSize;
		commandList->SetGraphicsRootConstantBufferView(0, cbAddress);
	}

	void ColorShader::DrawPassFrame(ID3D12GraphicsCommandList* commandList)
	{
		commandList->SetGraphicsRootConstantBufferView(1, m_ColorPassCB->GetGPUVirtualAddress());
	}

	void ColorShader::CreateShader()
	{
		m_VSBlob = CompileShader(L"Color.hlsl", "VSMain", "vs_5_1");
		m_PSBlob = CompileShader(L"Color.hlsl", "PSMain", "ps_5_1");
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

	void ColorShader::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, UINT numOfObject)
	{
		if (m_WorldMatCB != nullptr)
		{
			m_WorldMatCB->Unmap(0, nullptr);
			m_WorldMatCB->Release();
			m_WorldMatCB = nullptr;
		}

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
	
		/*if (m_ColorPassCB != nullptr)
		{
			m_ColorPassCB->Unmap(0, nullptr);
			m_ColorPassCB->Release();
		}

		UINT ColorPassCBByteSize = ((sizeof(CBColorPass) + 255) & ~255);
		m_ColorPassCB = D3DUtil::CreateBufferResource(device, commandList, nullptr, ColorPassCBByteSize,
			D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

		m_ColorPassCB->Map(0, nullptr, (void**)&m_MappedColorPass);*/

		if (m_ColorPassCB == nullptr)
		{
			UINT ColorPassCBByteSize = ((sizeof(CBColorPass) + 255) & ~255);
			m_ColorPassCB = D3DUtil::CreateBufferResource(device, commandList, nullptr, ColorPassCBByteSize,
				D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

			if (FAILED(m_ColorPassCB->Map(0, nullptr, (void**)&m_ColorPassMappedData)))
			{
				PARS_ERROR("ColorPass Mapping Error");
			}
		}
	}
}
