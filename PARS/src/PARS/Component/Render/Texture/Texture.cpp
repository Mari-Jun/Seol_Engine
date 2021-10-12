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

	void Texture::CreateTexture(ID3D12Device* device, UINT width, UINT height,
		DXGI_FORMAT format, D3D12_RESOURCE_FLAGS resourceFlags, D3D12_RESOURCE_STATES resourceStates,
		D3D12_CLEAR_VALUE* clearValue, UINT textureType)
	{
		m_TextureResource = D3DUtil::CreateTexture2DResource(device, width, height, 1, 0, format, resourceFlags, resourceStates, clearValue);
	}

	void Texture::LoadTextureFromDDSFile(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		std::wstring path(m_AssetInfo.path.begin(), m_AssetInfo.path.end());
		path += L".dds";
		m_TextureResource = D3DUtil::CreateTextureResourceFromDDSFile(device, commandList, path.c_str(), &m_IsCubeMap,
			&m_TextureUploadBuffer, D3D12_RESOURCE_STATE_GENERIC_READ);
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC Texture::GetShaderResourceViewDesc()
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
		D3D12_RESOURCE_DESC rscDesc = m_TextureResource->GetDesc();

		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = rscDesc.Format;

		if (m_IsCubeMap)
		{
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
			srvDesc.TextureCube.MipLevels = -1;
			srvDesc.TextureCube.MostDetailedMip = 0;
			srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
		}
		else
		{
			switch (rscDesc.Dimension)
			{
			case D3D12_RESOURCE_DIMENSION_BUFFER:
				srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
				srvDesc.Buffer.FirstElement = 0;
				srvDesc.Buffer.NumElements = 1;
				srvDesc.Buffer.StructureByteStride = 0;
				srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
				if (rscDesc.DepthOrArraySize == 1)
				{
					srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
					srvDesc.Texture2D.MipLevels = -1;
					srvDesc.Texture2D.MostDetailedMip = 0;
					srvDesc.Texture2D.PlaneSlice = 0;
					srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
				}
				else
				{
					srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
					srvDesc.Texture2DArray.MipLevels = -1;
					srvDesc.Texture2DArray.MostDetailedMip = 0;
					srvDesc.Texture2DArray.PlaneSlice = 0;
					srvDesc.Texture2DArray.ResourceMinLODClamp = 0.0f;
					srvDesc.Texture2DArray.FirstArraySlice = 0;
					srvDesc.Texture2DArray.ArraySize = rscDesc.DepthOrArraySize;
				}
				break;
			}
		}


		return srvDesc;
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
