#include "stdafx.h"
#include "PARS/Renderer/Core/ResourceManager.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Util/DirectX12/d3dUtil.h"
#include "PARS/Util/DirectX12/DDSTextureLoader12.h"
#include "PARS/Util/Content/GraphicsAssetStore.h"
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

	void ResourceManager::CreateSRVHeap(const std::function<void(ID3D12DescriptorHeap* heap)>& function)
	{
		const auto& textures = GraphicsAssetStore::GetAssetStore()->GetTextures();

		D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
		srvHeapDesc.NumDescriptors = 1 + textures.size(); //1은 imgui를 위한 것
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
			const auto& matSize = GraphicsAssetStore::GetAssetStore()->GetMaterials().size() * sizeof(CBMaterial);

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
		const auto& textures = GraphicsAssetStore::GetAssetStore()->GetTextures();

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

		for (const auto& [path, texture] : textures)
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
		}
	}

	void ResourceManager::UpdateMaterialResource()
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
			cbMat.diffuseAlbedo = material->GetDiffuseAlbedo();
			cbMat.fresnelR0 = material->GetFresnelR0();
			cbMat.roughness = material->GetRoughness();
			const auto& texture = material->GetDiffuseTexture();
			cbMat.diffuseMapIndex = texture != nullptr ? material->GetDiffuseTexture()->GetTextureSRVIndex() : -1;
			memcpy(&m_MaterialMappedData[matIndex * sizeof(CBMaterial)], &cbMat, sizeof(CBMaterial));
			++matIndex;
		}
	}

	void ResourceManager::UpdateTextureResource()
	{
		
	}
}