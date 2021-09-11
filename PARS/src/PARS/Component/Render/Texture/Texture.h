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

		ID3D12Resource* m_TextureResource = nullptr;
		ID3D12Resource* m_TextureUploadBuffer = nullptr;

		UINT m_TextureType = 0;

	public:
		void SetFilePath(const std::string& path) { m_FilePath = path; }
		void SetName(const std::string& name) { m_Name = name; }
		const std::string& GetName() const { return m_Name; }
		UINT GetTextureType() const { return m_TextureType; }

		ID3D12Resource* GetResource() { return m_TextureResource; }
	};

	namespace TEXTURE
	{
		SPtr<Texture> LoadDDS(const std::string& path, const std::string& stem);
	}
}

