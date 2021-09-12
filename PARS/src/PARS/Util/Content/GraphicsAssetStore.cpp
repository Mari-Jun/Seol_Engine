#include "stdafx.h"
#include "PARS/Util/Content/AssetStore.h"
#include "PARS/Util/Content/GraphicsAssetStore.h"
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Component/Render/Texture/Texture.h"


namespace PARS
{
	GraphicsAssetStore::GraphicsAssetStore()
	{
	}

	bool GraphicsAssetStore::Initialize()
	{
		s_Instance = this;
		return true;
	}

	void GraphicsAssetStore::Shutdown()
	{
		for (auto iter = m_MeshCache.begin(); iter != m_MeshCache.end(); ++iter)
			iter->second->Shutdown();
		m_MeshCache.clear();

		m_MaterialCache.clear();

		for (auto iter = m_TextureCache.begin(); iter != m_TextureCache.end(); ++iter)
			iter->second->Shutdown();
		m_TextureCache.clear();
	}

	const SPtr<Mesh>& GraphicsAssetStore::GetMesh(const std::string& path) const
	{
		auto iter = m_MeshCache.find(path);
		if (iter != m_MeshCache.end())
		{
			return iter->second;
		}

		return nullptr;
	}

	void GraphicsAssetStore::LoadMesh(std::multimap<std::string, std::string>& contents, const std::string& path)
	{
		std::string extension = FILEHELP::GetExtentionFromPath(path);
		if (extension == ".obj")
		{
			std::string parentPath = FILEHELP::GetParentPathFromPath(path);

			for (SPtr<MaterialMesh>& mesh : OBJ::LoadObj(path, parentPath))
			{
				std::string realPath = parentPath + "\\" + mesh->GetObjectName();
				m_MeshCache.emplace(realPath, mesh);
				contents.emplace(mesh->GetObjectName(), realPath);
			}
		}
	}

	const SPtr<Material>& GraphicsAssetStore::GetMaterial(const std::string& path) const
	{
		auto iter = m_MaterialCache.find(path);
		if (iter != m_MaterialCache.end())
		{
			return iter->second;
		}

		return nullptr;
	}

	void GraphicsAssetStore::LoadMaterial(std::multimap<std::string, std::string>& contents, const std::string& path)
	{
		std::string extension = FILEHELP::GetExtentionFromPath(path);
		if (extension == ".mtl")
		{
			std::string parentPath = FILEHELP::GetParentPathFromPath(path);

			for (SPtr<Material>& material : MTL::LoadMtl(path))
			{
				std::string realPath = parentPath + "\\" + material->GetName();
				m_MaterialCache.emplace(realPath, material);
				contents.emplace(material->GetName(), realPath);
			}
		}
	}

	const SPtr<Texture>& GraphicsAssetStore::GetTexture(const std::string& path) const
	{
		auto iter = m_TextureCache.find(path);
		if (iter != m_TextureCache.end())
		{
			return iter->second;
		}

		return nullptr;
	}

	void GraphicsAssetStore::LoadTexture(std::multimap<std::string, std::string>& contents, const std::string& path)
	{
		std::string extension = FILEHELP::GetExtentionFromPath(path);
		if (extension == ".dds")
		{
			std::string parentPath = FILEHELP::GetParentPathFromPath(path);
			std::string stem = FILEHELP::GetStemFromPath(path);

			SPtr<Texture> texture = TEXTURE::LoadDDS(path, stem);

			if (texture != nullptr)
			{
				std::string realPath = parentPath + "\\" + texture->GetName();
				m_TextureCache.emplace(realPath, texture);
				contents.emplace(texture->GetName(), realPath);
			}
		}
	}

	void GraphicsAssetStore::ConvertToPARSFile(const std::string& path)
	{
		std::cout << path << std::endl;

		std::ifstream file(path);
		if (file)
		{
			std::string fileOut = { path + "PARS" };
			std::ofstream out(fileOut, std::ios_base::binary);
			std::copy(std::istream_iterator<std::string> {file}, std::istream_iterator<std::string>{}, std::ostream_iterator<std::string> {out, " "});
		}
	}

	GraphicsAssetStore* GraphicsAssetStore::s_Instance = nullptr;
}
