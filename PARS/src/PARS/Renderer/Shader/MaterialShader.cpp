#include "stdafx.h"
#include "PARS/Renderer/Shader/MaterialShader.h"
#include "PARS/Component/Render/Mesh/Mesh.h"

namespace PARS
{
	MaterialShader::MaterialShader(const SPtr<DirectX12>& directX)
		: Shader(directX)
	{
		m_Type = ShaderType::Material;
	}

	void MaterialShader::CreateShader()
	{
		m_VSBlob = CompileShader(L"Default.hlsl", "VSMaterialMain", "vs_5_1");
		m_PSBlob = CompileShader(L"Default.hlsl", "PSMaterialMain", "ps_5_1");
	}

	void MaterialShader::CreateInputLayout()
	{
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
		m_InputLayouts.emplace_back(D3D12_INPUT_ELEMENT_DESC{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 });
	}

	bool MaterialShader::CreatePSO(ID3D12RootSignature* rootSignature)
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
