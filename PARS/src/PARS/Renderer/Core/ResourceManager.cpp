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
		const auto& assetStore = AssetStore::GetAssetStore();

		if (assetStore->IsAddedNewItemForType(AssetType::Texture))
		{
			if (m_TextureDescriptorHeap != nullptr)
			{
				m_TextureDescriptorHeap->Release();
			}

			D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
			srvHeapDesc.NumDescriptors = /*assetStore->GetTextureAssetCount()*/65536;
			srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			srvHeapDesc.NodeMask = 0;
			if (FAILED(m_DirectX12->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&m_TextureDescriptorHeap))))
			{
				PARS_ERROR("Colud not create descriptor heap");
			}

			m_TextureDescriptorHeap->SetName(L"Texture Descriptor");

			function(m_TextureDescriptorHeap);

			
		}

		
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
		const auto& assetStore = AssetStore::GetAssetStore();

		if (assetStore->IsAddedNewItemForType(AssetType::Texture))
		{
			D3D12_CPU_DESCRIPTOR_HANDLE desCPUHandle(m_TextureDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
			D3D12_GPU_DESCRIPTOR_HANDLE desGPUHandle(m_TextureDescriptorHeap->GetGPUDescriptorHandleForHeapStart());

			//imgui를 위해 1칸씩 띄운다.
			desCPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
			desGPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

			int index = 0;

			AssetStore::GetAssetStore()->OnAllTextureAssetExecuteFunction(
				[this, &device, &commandList, &index, &desCPUHandle, &desGPUHandle](const SPtr<Texture>& texture)
				{
					if (texture->GetResource() == nullptr)
					{
						switch (HashCode(texture->GetExtension().c_str()))
						{
						case HashCode(".dds"):
							texture->LoadTextureFromDDSFile(device, commandList);
							break;
						default:
							break;
						}
					}

					device->CreateShaderResourceView(texture->GetResource(), &texture->GetShaderResourceViewDesc(), desCPUHandle);
					desCPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
					texture->SetTextureSRVIndex(++index);
					texture->SetGpuHandle(desGPUHandle);
					desGPUHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
				});
		}
	}

	void ResourceManager::UpdateMaterialResource()
	{
		//마찬가지로 이 부분도 계속 업데이트 할 필요가 없다.
		//새로운 Material이 생성되면 그 때 업데이트 하면 된다.
		//일단은 그 부분은 생각해야 할 부분이 있기 때문에 지금은 임시로 매 프레임마다 업데이트 되게 한다.
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