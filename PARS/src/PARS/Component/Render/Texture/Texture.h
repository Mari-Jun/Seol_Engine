#pragma once
#include "PARS/Util/Content/Asset.h"

namespace PARS
{
	class Texture : public Asset
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;


		virtual void Shutdown() override;
		void ReleaseUploadBuffers();

		void CreateTexture(ID3D12Device* device, UINT width, UINT height,
			DXGI_FORMAT format, D3D12_RESOURCE_FLAGS resourceFlags, D3D12_RESOURCE_STATES resourceStates,
			D3D12_CLEAR_VALUE* clearValue, UINT textureType);

		void LoadTextureFromDDSFile(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		D3D12_SHADER_RESOURCE_VIEW_DESC GetShaderResourceViewDesc();
		
	private:
		UINT m_TextureSRVIndex = 0;

		ID3D12Resource* m_TextureResource = nullptr;
		ID3D12Resource* m_TextureUploadBuffer = nullptr;

		D3D12_GPU_DESCRIPTOR_HANDLE m_GPUHandle;

		bool m_IsCubeMap = false;
		D3D12_RESOURCE_DIMENSION m_TextureType;

	public:
		void SetTextureSRVIndex(UINT index) { m_TextureSRVIndex = index; }
		UINT GetTextureSRVIndex() const { return m_TextureSRVIndex; }
		D3D12_RESOURCE_DIMENSION GetTextureType() const { return m_TextureType; }

		ID3D12Resource* GetResource() { return m_TextureResource; }
		void SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE handle) { m_GPUHandle = handle; }
		D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle() const { return m_GPUHandle; }
	};

	namespace TEXTURE
	{
		SPtr<Texture> LoadDDS(const std::string& path, const std::string& stem);
	}
}

