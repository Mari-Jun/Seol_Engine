#include "stdafx.h"
#include "PARS/Renderer/Shader/Core/Shader.h"
#include "PARS/Renderer/Core/RenderItem.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	std::wstring Shader::s_ShaderFilePath = L"../PARS/src/PARS/Renderer/Shader/HLSL/";

	Shader::Shader(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
	}

	bool Shader::Initialize(ID3D12RootSignature* rootSignature)
	{
		CreateShader();
		CreateInputLayout();

		if (!CreatePSO(rootSignature)) return false;
	
		return true;
	}

	void Shader::Shutdown()
	{
		for (auto& renderItem : m_RenderItems)
			renderItem->Shutdown();
		m_RenderItems.clear();

		if (m_PipelineState != nullptr) m_PipelineState->Release();
		m_PipelineState = nullptr;
		if (m_VSBlob != nullptr) m_VSBlob->Release();
		m_VSBlob = nullptr;
		if (m_PSBlob != nullptr) m_PSBlob->Release();
		m_PSBlob = nullptr;
	}

	void Shader::Update(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		for (const auto& renderItem : m_RenderItems)
		{
			renderItem->Update(device, commandList);
		}
	}

	void Shader::Draw(ID3D12GraphicsCommandList* commandList)
	{
		m_DirectX12->GetCommandList()->SetPipelineState(GetPipelineState());

		for (const auto& renderItem : m_RenderItems)
		{
			renderItem->Draw(commandList);
		}
	}

	D3D12_RASTERIZER_DESC Shader::CreateRasterizerState()
	{
		D3D12_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
		rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		rasterizerDesc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		rasterizerDesc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		rasterizerDesc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		rasterizerDesc.DepthClipEnable = TRUE;
		rasterizerDesc.MultisampleEnable = FALSE;
		rasterizerDesc.AntialiasedLineEnable = FALSE;
		rasterizerDesc.ForcedSampleCount = 0;
		rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

		return rasterizerDesc;
	}

	D3D12_BLEND_DESC Shader::CreateBlendState()
	{
		D3D12_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.IndependentBlendEnable = FALSE;

		const D3D12_RENDER_TARGET_BLEND_DESC RTBDesc =
		{
			FALSE, FALSE,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP,
			D3D12_COLOR_WRITE_ENABLE_ALL,
		};
		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
			blendDesc.RenderTarget[i] = RTBDesc;

		return blendDesc;
	}

	D3D12_DEPTH_STENCIL_DESC Shader::CreateDepthStencilState()
	{
		D3D12_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		depthStencilDesc.StencilEnable = FALSE;
		depthStencilDesc.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
		depthStencilDesc.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
		const D3D12_DEPTH_STENCILOP_DESC dsopDesc =
		{
			D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS
		};
		depthStencilDesc.FrontFace = dsopDesc;
		depthStencilDesc.BackFace = dsopDesc;

		return depthStencilDesc;
	}


	ID3DBlob* Shader::CompileShader(std::wstring&& fileName, std::string&& entryPoint, std::string&& target)
	{
		UINT compileFlags = 0;
#if defined(_DEBUG)
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES;
#endif
		std::wstring filePath = s_ShaderFilePath + fileName;

		ID3DBlob* byteCode = nullptr;
		ID3DBlob* error;

		D3DCompileFromFile(filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &error);

		if (error != nullptr)
		{
			OutputDebugStringA((char*)error->GetBufferPointer());
			error->Release();
		}

		return byteCode;
	}

	void Shader::AddMeshCompForDraw(const SPtr<MeshComponent>& meshComp)
	{
		const auto& mesh = meshComp->GetMesh();

		auto iter = find_if(m_RenderItems.begin(), m_RenderItems.end(), [&mesh](const SPtr<RenderItem>& renderItem)
			{ return mesh == renderItem->GetMesh(); });

		if (iter != m_RenderItems.end())
		{
			iter->get()->AddMeshCompDrwanWithMesh(meshComp);
		}
		else
		{
			UINT matSize = static_cast<UINT>(meshComp->GetMaterials().size());
			SPtr<RenderItem> renderItem = CreateSPtr<RenderItem>(mesh, matSize);
			renderItem->AddMeshCompDrwanWithMesh(meshComp);
			m_RenderItems.emplace_back(std::move(renderItem));
		}
	}

	void Shader::RemoveMeshCompForDraw(const SPtr<class MeshComponent>& meshComp)
	{
		const auto & mesh = meshComp->GetMesh();

		auto iter = find_if(m_RenderItems.begin(), m_RenderItems.end(), [&mesh](const SPtr<RenderItem>& renderItem)
			{ return mesh == renderItem->GetMesh(); });

		if (iter != m_RenderItems.end())
		{
			if (iter->get()->RemoveInstanceData(meshComp))
			{
				iter->get()->Shutdown();
				m_RenderItems.erase(iter);
			}
		}
	}
}