#pragma once
#include "PARS/Core/Core.h"

namespace PARS
{
	class DirectX12;

	class ResourceManager
	{
	public:
		ResourceManager(const SPtr<DirectX12>& directX);

		void Initialize();
		void Shutdown();
		void Update();
		void Draw();
		void PrepareToNextDraw();

	public:
		void CreateSRVHeap(const std::function<void(ID3D12DescriptorHeap* heap)>& function);
		void CreateMaterialResource(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		void CreateTextureResource(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		void UpdateMaterialResource();
		void UpdateTextureResource();

	private:
		SPtr<DirectX12> m_DirectX12;

		ID3D12Resource* m_MaterialResource = nullptr;
		BYTE* m_MaterialMappedData = nullptr;

		ID3D12DescriptorHeap* m_TextureDescriptorHeap = nullptr;

	public:
		const SPtr<DirectX12>& GetDirectX12() const { return m_DirectX12; }
		ID3D12Resource* GetMaterialResource() const { return m_MaterialResource; }
		ID3D12DescriptorHeap* GetTextureDescriptorHeap() { return m_TextureDescriptorHeap; }
	};
}


