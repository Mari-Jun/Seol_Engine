#pragma once
#include "PARS/Core/Core.h"

namespace PARS
{
	class Texture
	{
	public:
		Texture();

		void Shutdown();
		void ReleaseUploadBuffers();

		void LoadTextureFromDDSFile(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, UINT textureType);
		
	private:
		std::string m_FilePath;
		std::string m_Name;

		UINT m_TextureSRVIndex = 0;

		ID3D12Resource* m_TextureResource = nullptr;
		ID3D12Resource* m_TextureUploadBuffer = nullptr;

		D3D12_GPU_DESCRIPTOR_HANDLE m_GPUHandle;

		UINT m_TextureType = 0;

	public:
		void SetFilePath(const std::string& path) { m_FilePath = path; }
		void SetName(const std::string& name) { m_Name = name; }
		const std::string& GetName() const { return m_Name; }
		void SetTextureSRVIndex(UINT index) { m_TextureSRVIndex = index; }
		UINT GetTextureSRVIndex() const { return m_TextureSRVIndex; }
		UINT GetTextureType() const { return m_TextureType; }

		ID3D12Resource* GetResource() { return m_TextureResource; }
		void SetGpuHandle(D3D12_GPU_DESCRIPTOR_HANDLE handle) { m_GPUHandle = handle; }
		D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle() const { return m_GPUHandle; }
	};

	namespace TEXTURE
	{
		SPtr<Texture> LoadDDS(const std::string& path, const std::string& stem);
	}
}

