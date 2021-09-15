#include "stdafx.h"
#include "PARS/Component/Render/Texture/Texture.h"
#include "PARS/Util/DirectX12/d3dUtil.h"

namespace PARS
{
	void Texture::Shutdown()
	{
		if (m_TextureResource != nullptr)
		{
			m_TextureResource->Release();
			m_TextureResource = nullptr;
		}
		ReleaseUploadBuffers();
	}

	void Texture::ReleaseUploadBuffers()
	{
		if (m_TextureUploadBuffer != nullptr)
		{
			m_TextureUploadBuffer->Release();
			m_TextureUploadBuffer = nullptr;
		}
	}

	void Texture::LoadTextureFromDDSFile(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, UINT textureType)
	{
		m_TextureType = textureType;
		std::wstring path(m_AssetInfo.path.begin(), m_AssetInfo.path.end());
		path += L".dds";
		m_TextureResource = D3DUtil::CreateTextureResourceFromDDSFile(device, commandList, path.c_str(),
			&m_TextureUploadBuffer, D3D12_RESOURCE_STATE_GENERIC_READ);
	}

	namespace TEXTURE
	{
		SPtr<Texture> LoadDDS(const std::string& path, const std::string& stem)
		{
			SPtr<Texture> texture = CreateSPtr<Texture>();
			texture->SetName(stem);
			return texture;
		}
	}
}
