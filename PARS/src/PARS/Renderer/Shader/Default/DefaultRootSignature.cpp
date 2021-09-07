#include "stdafx.h"
#include "PARS/Renderer/Shader/Default/DefaultRootSignature.h"
#include "PARS/Renderer/Shader/ColorShader.h"
#include "PARS/Renderer/Shader/MaterialShader.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Util/Content/GraphicsAssetStore.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	DefaultRootSignature::DefaultRootSignature(const SPtr<DirectX12>& directX)
		: RootSignature(directX)
	{
	}

	void DefaultRootSignature::Shutdown()
	{
		if (m_DefaultPassCB != nullptr)
		{
			m_DefaultPassCB->Unmap(0, nullptr);
			m_DefaultPassCB->Release();
		}

		if (m_MaterialCB != nullptr)
		{
			m_MaterialCB->Unmap(0, nullptr);
			m_MaterialCB->Release();
		}

		RootSignature::Shutdown();
	}

	void DefaultRootSignature::CreateRootSignature(ID3D12Device* device)
	{
		D3D12_ROOT_PARAMETER rootParameter[4];
		rootParameter[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[0].Descriptor.ShaderRegister = 0;
		rootParameter[0].Descriptor.RegisterSpace = 0;
		rootParameter[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		rootParameter[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[1].Descriptor.ShaderRegister = 1;
		rootParameter[1].Descriptor.RegisterSpace = 0;
		rootParameter[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameter[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_SRV;
		rootParameter[2].Descriptor.ShaderRegister = 0;
		rootParameter[2].Descriptor.RegisterSpace = 0;
		rootParameter[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		rootParameter[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
		rootParameter[3].Descriptor.ShaderRegister = 2;
		rootParameter[3].Descriptor.RegisterSpace = 0;
		rootParameter[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

		D3D12_ROOT_SIGNATURE_DESC rsDesc;
		rsDesc.NumParameters = _countof(rootParameter);
		rsDesc.pParameters = rootParameter;
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

		if (m_MaterialCB == nullptr)
		{
			const auto& matSize = GraphicsAssetStore::GetAssetStore()->GetMaterials().size() * sizeof(CBMaterial);

			m_MaterialCB = D3DUtil::CreateBufferResource(device, commandList, nullptr, matSize,
				D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

			if (FAILED(m_MaterialCB->Map(0, nullptr, (void**)&m_MaterialMappedData)))
			{
				PARS_ERROR("MaterialCB Mapping Error");
			}
		}
	}

	void DefaultRootSignature::UpdateShaderVariables()
	{

		//마찬가지로 이 부분도 계속 업데이트 할 필요가 없다.
		//새로운 Material이 생성되면 그 때 업데이트 하면 된다.
		//일단은 그 부분은 생각해야 할 부분이 있기 때문에 지금은 임시로 매 프레임마다 업데이트 되게 한다.
		const auto& assetStore = GraphicsAssetStore::GetAssetStore();

		int matIndex = 0;
		for (const auto& [path, material] : assetStore->GetMaterials())
		{
			material->SetMatCBIndex(matIndex);

			CBMaterial cbMat;
			cbMat.DiffuseAlbedo = material->GetDiffuseAlbedo();
			cbMat.FresnelR0 = material->GetFresnelR0();
			cbMat.Shininess = 1.0f - material->GetRoughness();

			memcpy(&m_MaterialMappedData[matIndex * sizeof(CBMaterial)], &cbMat, sizeof(CBMaterial));
			++matIndex;
		}

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
		commandList->SetGraphicsRootShaderResourceView(2, m_MaterialCB->GetGPUVirtualAddress());
		commandList->SetGraphicsRootConstantBufferView(3, m_DefaultPassCB->GetGPUVirtualAddress());
	}
}
