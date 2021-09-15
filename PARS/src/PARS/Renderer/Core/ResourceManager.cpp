#include "stdafx.h"
#include "PARS/Renderer/Core/ResourceManager.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Util/DirectX12/d3dUtil.h"
#include "PARS/Util/DirectX12/DDSTextureLoader12.h"
#include "PARS/Util/Content/AssetStore.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Component/Render/Texture/Texture.h"

namespace PARS
{
	ResourceManager::ResourceManager(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
	}

	void ResourceManager::Initialize()
	{

	}

	void ResourceManager::Shutdown()
	{
		if (m_MaterialResource != nullptr)
		{
			m_MaterialResource->Unmap(0, nullptr);
			m_MaterialResource->Release();
		}

		if (m_TextureDescriptorHeap != nullptr)
		{
			m_TextureDescriptorHeap->Release();
		}
	}

	void ResourceManager::Update()
	{
		CreateMaterialResource(m_DirectX12->GetDevice(), m_DirectX12->GetCommandList());
		CreateTextureResource(m_DirectX12->GetDevice(), m_DirectX12->GetCommandList());

		UpdateMaterialResource();
		UpdateTextureResource();
	}

	void ResourceManager::Draw()
	{
		ID3D12DescriptorHeap* descriptorHeaps[] = { m_TextureDescriptorHeap };
		m_DirectX12->GetCommandList()->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	}

	void ResourceManager::PrepareToNextDraw()
	{
		AssetStore::GetAssetStore()->OnAllTextureAssetExecuteFunction(
			[this](const SPtr<Texture>& texture)
			{
				texture->ReleaseUploadBuffers();
			});
	}

	void ResourceManager::CreateSRVHeap(const std::function<void(ID3D12DescriptorHeap* heap)>& function)
	{
		D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
		srvHeapDesc.NumDescriptors = 1 + AssetStore::GetAssetStore()->GetTextureAssetCount(); //1�� imgui�� ���� ��
		srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		srvHeapDesc.NodeMask = 0;
		if (FAILED(m_DirectX12->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_TextureDescriptorHeap))))
		{
			PARS_ERROR("Colud not create descriptor heap");
		}

		function(m_TextureDescriptorHeap);
	}

	void ResourceManager::CreateMaterialResource(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		if (m_MaterialResource == nullptr)
		{
			const auto& matSize = AssetStore::GetAssetStore()->GetMaterialAssetCount() * sizeof(CBMaterial);

			m_MaterialResource = D3DUtil::CreateBufferResource(device, commandList, nullptr, matSize,
				D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

			if (FAILED(m_MaterialResource->Map(0, nullptr, (void**)&m_MaterialMappedData)))
			{
				PARS_ERROR("MaterialResource Mapping Error");
			}
		}
	}

	void ResourceManager::CreateTextureResource(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE desCPUHandle(m_TextureDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
		D3D12_GPU_DESCRIPTOR_HANDLE desGPUHandle(m_TextureDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		desCPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
		desGPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

		int index = 0;

		AssetStore::GetAssetStore()->OnAllTextureAssetExecuteFunction(
			[this, &device, &commandList, &index, &srvDesc, &desCPUHandle, &desGPUHandle](const SPtr<Texture>& texture)
			{
				if (texture->GetResource() == nullptr)
				{
					texture->LoadTextureFromDDSFile(device, commandList, 0x01);
					texture->SetTextureSRVIndex(index++);
					srvDesc.Format = texture->GetResource()->GetDesc().Format;
					srvDesc.Texture2D.MipLevels = texture->GetResource()->GetDesc().MipLevels;
					device->CreateShaderResourceView(texture->GetResource(), &srvDesc, desCPUHandle);
					desCPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
					texture->SetGpuHandle(desGPUHandle);
					desGPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
				}
			});
	}

	void ResourceManager::UpdateMaterialResource()
	{
		//���������� �� �κе� ��� ������Ʈ �� �ʿ䰡 ����.
		//���ο� Material�� �����Ǹ� �� �� ������Ʈ �ϸ� �ȴ�.
		//�ϴ��� �� �κ��� �����ؾ� �� �κ��� �ֱ� ������ ������ �ӽ÷� �� �����Ӹ��� ������Ʈ �ǰ� �Ѵ�.
		int matIndex = 0;
		AssetStore::GetAssetStore()->OnAllMaterialAssetExecuteFunction([this, &matIndex](const SPtr<Material>& material)
			{
				material->SetMatCBIndex(matIndex);

				CBMaterial cbMat;
				cbMat.diffuseAlbedo = material->GetDiffuseAlbedo();
				cbMat.fresnelR0 = material->GetFresnelR0();
				cbMat.roughness = material->GetRoughness();
				const auto& texture = material->GetDiffuseTexture();
				cbMat.diffuseMapIndex = texture != nullptr ? material->GetDiffuseTexture()->GetTextureSRVIndex() : -1;
				memcpy(&m_MaterialMappedData[matIndex * sizeof(CBMaterial)], &cbMat, sizeof(CBMaterial));
				++matIndex;
			});
	}

	void ResourceManager::UpdateTextureResource()
	{
		
	}
}