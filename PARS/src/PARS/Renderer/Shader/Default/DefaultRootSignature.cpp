#include "stdafx.h"
#include "PARS/Renderer/Core/ResourceManager.h"
#include "PARS/Renderer/Shader/Default/DefaultRootSignature.h"
#include "PARS/Renderer/Shader/ColorShader.h"
#include "PARS/Renderer/Shader/MaterialShader.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Component/Render/Texture/Texture.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	DefaultRootSignature::DefaultRootSignature(const SPtr<ResourceManager>& resourceManager)
		: RootSignature(resourceManager)
	{
	}

	void DefaultRootSignature::Shutdown()
	{
		if (m_DefaultPassCB != nullptr)
		{
			m_DefaultPassCB->Unmap(0, nullptr);
			m_DefaultPassCB->Release();
		}

		if (m_SrvDescriptorHeap != nullptr)
		{
			m_SrvDescriptorHeap->Release();
		}

		RootSignature::Shutdown();
	}

	void DefaultRootSignature::CreateRootSignature(ID3D12Device* device)
	{
		D3D12_DESCRIPTOR_RANGE descriptorRanges[1];
		descriptorRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		descriptorRanges[0].NumDescriptors = -1;
		descriptorRanges[0].BaseShaderRegister = 3; 
		descriptorRanges[0].RegisterSpace = 0;
		descriptorRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;		

		D3D12_ROOT_PARAMETER rootParameter[5];
		rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
		rootParameter[0].Descriptor.ShaderRegister = 0;
		rootParameter[0].Descriptor.RegisterSpace = 0;
		rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
		rootParameter[1].Descriptor.ShaderRegister = 1;
		rootParameter[1].Descriptor.RegisterSpace = 0;
		rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameter[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
		rootParameter[2].Descriptor.ShaderRegister = 2;
		rootParameter[2].Descriptor.RegisterSpace = 0;
		rootParameter[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameter[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
		rootParameter[3].DescriptorTable.NumDescriptorRanges = 1;
		rootParameter[3].DescriptorTable.pDescriptorRanges = &descriptorRanges[0];
		rootParameter[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameter[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[4].Descriptor.ShaderRegister = 1;
		rootParameter[4].Descriptor.RegisterSpace = 0;
		rootParameter[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		D3D12_STATIC_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
		samplerDesc.MipLODBias = 0;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
		samplerDesc.ShaderRegister = 0;
		samplerDesc.RegisterSpace = 0;
		samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

		D3D12_ROOT_SIGNATURE_DESC rsDesc;
		rsDesc.NumParameters = _countof(rootParameter);
		rsDesc.pParameters = rootParameter;
		rsDesc.NumStaticSamplers = 1;
		rsDesc.pStaticSamplers = &samplerDesc;
		rsDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob* signatureBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		HRESULT result = D3D12SerializeRootSignature(&rsDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);

		if (errorBlob != nullptr)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}

		device->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&m_RootSignature));

		if (signatureBlob != nullptr)
		{
			signatureBlob->Release();
		}
		if (errorBlob != nullptr)
		{
			errorBlob->Release();
		}
	}

	void DefaultRootSignature::CreateShaders()
	{
		if (m_DirectX12 != nullptr)
		{
			CreateShader(CreateSPtr<ColorShader>(m_DirectX12));
			CreateShader(CreateSPtr<MaterialShader>(m_DirectX12));
		}
	}

	void DefaultRootSignature::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		if (m_DefaultPassCB == nullptr)
		{
			UINT DefaultPassCBByteSize = ((sizeof(CBDefaultPass) + 255) & ~255);
			m_DefaultPassCB = D3DUtil::CreateBufferResource(device, commandList, nullptr, DefaultPassCBByteSize,
				D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

			if (FAILED(m_DefaultPassCB->Map(0, nullptr, (void**)&m_DefaultPassMappedData)))
			{
				PARS_ERROR("ColorPass Mapping Error");
			}
		}
	}

	void DefaultRootSignature::UpdateShaderVariables()
	{
		const auto& factory = RenderFactory::GetRenderFactory();
		CBDefaultPass cbPass;

		for (const auto& camera : factory->GetCameraComps())
		{
			if (camera->IsActive())
			{
				Mat4 viewProj;

				viewProj = camera->GetViewMatrix();
				viewProj *= camera->GetProjection();
				viewProj.Transpose();

				const Vec3& eyePos = camera->GetOwner().lock()->GetPosition();

				cbPass.m_ViewProj = viewProj;
				cbPass.m_EyePos = eyePos;

				std::vector<LightCB> lights;
				LightCount lightCount;
				for (const auto& light : factory->GetLightComps())
				{
					lights.push_back(light->GetLightCB());
					lightCount.AddLightCount(light->GetLightType());
				}

				cbPass.m_LightCount = lightCount;
				cbPass.m_AmbientLight = { 0.25f, 0.25f, 0.25f, 1.0f };
				if (!lights.empty())
					*cbPass.m_Lights = *lights.data();
				else
					cbPass.m_AmbientLight = { 1.0f,  1.0f, 1.0f, 1.0f };
			}
		}

		memcpy(m_DefaultPassMappedData, &cbPass, sizeof(CBDefaultPass));
	}

	void DefaultRootSignature::DrawPassFrame(ID3D12GraphicsCommandList* commandList)
	{
		commandList->SetGraphicsRootShaderResourceView(2, m_ResourceManager->GetMaterialResource()->GetGPUVirtualAddress());
		commandList->SetGraphicsRootDescriptorTable(3, m_ResourceManager->GetTextureDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
		commandList->SetGraphicsRootConstantBufferView(4, m_DefaultPassCB->GetGPUVirtualAddress());
	}
}
