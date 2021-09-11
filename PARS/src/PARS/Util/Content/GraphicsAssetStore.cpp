#include "stdafx.h"
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

	void GraphicsAssetStore::LoadMesh(const std::string& path, const std::string& parentPath, const std::string& extension)
	{
		if (extension == ".obj")
		{
			std::vector<SPtr<MaterialMesh>> meshes = OBJ::LoadObj(path, parentPath);

			for (SPtr<MaterialMesh>& mesh : meshes)
				m_MeshCache.emplace(parentPath + "\\" + mesh->GetObjectName(), mesh);
			
		}
		//ConvertToPARSFile(path);
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

	void GraphicsAssetStore::LoadMaterial(const std::string& path, const std::string& parentPath, const std::string& extension)
	{
		if (extension == ".mtl")
		{
			for (SPtr<Material>& material : MTL::LoadMtl(path))
				m_MaterialCache.emplace(parentPath + "\\" + material->GetName(), material);
		}
	}

	void GraphicsAssetStore::SaveMaterial(const std::string& name, const SPtr<Material>& material)
	{
		m_MaterialCache.emplace(name, material);
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

	void GraphicsAssetStore::LoadTexture(const std::string& path, const std::string& parentPath, const std::string& stem, const std::string& extension)
	{
		if (extension == ".dds")
		{
			SPtr<Texture> texture = TEXTURE::LoadDDS(path, stem);
			m_TextureCache.emplace(parentPath + "\\" + texture->GetName(), texture);
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
