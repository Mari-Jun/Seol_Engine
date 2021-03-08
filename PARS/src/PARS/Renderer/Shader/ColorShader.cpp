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
		if (m_PassFrameCB != nullptr)
		{
			m_PassFrameCB->Unmap(0, nullptr);
			m_PassFrameCB->Release();
		}
		if (m_WorldMatCB != nullptr)
		{
			m_WorldMatCB->Unmap(0, nullptr);
			m_WorldMatCB->Release();
		}
	}

	void ColorShader::UpdateShaderVariables(ID3D12GraphicsCommandList* commandList, const std::vector<SPtr<RenderComponent>>& renderComps, const CBPassFrame& cbPass)
	{
		UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);
		for (int i = 0; i < renderComps.size(); ++i)
		{
			CBWorldMat* mappedWorldMat = (CBWorldMat*)m_MappedWorldMat + (i * worldCBByteSize);
			Mat4 worldMatrix = renderComps[i]->GetOwner().lock()->GetWorldMatrix();
			worldMatrix.Transpose();
			memcpy_s(&mappedWorldMat->m_WorldMatrix, sizeof(Mat4), &worldMatrix, sizeof(Mat4));
		}

		memcpy_s(&m_MappedPassFrame->m_ViewProj, sizeof(Mat4), &cbPass.m_ViewProj, sizeof(Mat4));
	}

	void ColorShader::DrawRenderComp(ID3D12GraphicsCommandList* commandList, const SPtr<RenderComponent>& renderComp, int index)
	{
		UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);
		D3D12_GPU_VIRTUAL_ADDRESS cbAddress = m_WorldMatCB->GetGPUVirtualAddress() + index * worldCBByteSize;
		commandList->SetGraphicsRootConstantBufferView(0, cbAddress);
	}

	void ColorShader::DrawPassFrame(ID3D12GraphicsCommandList* commandList)
	{
		commandList->SetGraphicsRootConstantBufferView(1, m_PassFrameCB->GetGPUVirtualAddress());
	}

	void ColorShader::CreateShader()
	{
		m_VSBlob = CompileShader(L"Color.hlsl", "VSMain", "vs_5_1");
		m_PSBlob = CompileShader(L"Color.hlsl", "PSMain", "ps_5_1");
	}

	void ColorShader::CreateInputLayout()
	{
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
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
		}

		UINT worldCBByteSize = ((sizeof(CBWorldMat) + 255) & ~255);
		m_WorldMatCB = D3DUtil::CreateBufferResource(device, commandList, nullptr, worldCBByteSize * numOfObject,
			D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

		m_WorldMatCB->Map(0, nullptr, (void**)&m_MappedWorldMat);

		//passFrame은 크기가 변하지 않아서 처음에만 실행시킨다.
		if (m_PassFrameCB == nullptr)
		{
			UINT passFrameCBByteSize = ((sizeof(CBPassFrame) + 255) & ~255);
			m_PassFrameCB = D3DUtil::CreateBufferResource(device, commandList, nullptr, passFrameCBByteSize,
				D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

			m_PassFrameCB->Map(0, nullptr, (void**)&m_MappedPassFrame);
		}
	}
}
