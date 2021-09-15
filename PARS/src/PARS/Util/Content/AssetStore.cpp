#include "stdafx.h"
#include "PARS/Util/Content/AssetStore.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Component/Render/Texture/Texture.h"

namespace PARS
{
	AssetStore* AssetStore::s_Instance = nullptr;

	AssetStore::AssetStore()
	{
		s_Instance = this;

		GetContents(ENGINE_CONTENT_DIR);
		ReloadContents();
	}

	void AssetStore::Shutdown()
	{
		m_SortedAssets.clear();
		m_LoadedContents.clear();
		for (const auto& [type, assetCache] : m_AssetCaches)
		{
			for (const auto& [path, asset] : assetCache)
			{
				asset->Shutdown();
			}
		}
	}

	void AssetStore::Update(float deltaTime)
	{
		static float time = 0.0f;
		time += deltaTime;

		if (time >= 1.0f)
		{
			//std::clock_t start = std::clock();
			ReloadContents();
			time -= 1.0f;
			//std::clock_t end = std::clock();

			//std::cout << difftime(end, start) << "ms" << std::endl;
		}
	}

	void AssetStore::ReloadContents()
	{
		GetContents(CONTENT_DIR);
	}

	void AssetStore::GetContents(const std::string& rootPath)
	{
		for (const auto& file : std::filesystem::directory_iterator(rootPath))
		{
			if (file.is_directory())
			{
				std::string dirPath = file.path().relative_path().u8string();
				GetContents(dirPath);
			}
			else if(file.is_regular_file())
			{
				std::string extension = FILEHELP::GetExtentionFromFile(file);
				std::string filePath = FILEHELP::GetPathFromFile(file);

				switch (HashCode(extension.c_str()))
				{
				case HashCode(".obj"):
					if (m_LoadedContents[AssetType::StaticMesh].find(filePath) == m_LoadedContents[AssetType::StaticMesh].cend())
						LoadMesh(filePath);
					break;
				case HashCode(".mtl"):
					if (m_LoadedContents[AssetType::Material].find(filePath) == m_LoadedContents[AssetType::Material].cend())
						LoadMaterial(filePath);
					break;
				case HashCode(".dds"):
					if (m_LoadedContents[AssetType::Texture].find(filePath) == m_LoadedContents[AssetType::Texture].cend())
						LoadTexture(filePath);
					break;
				default:
					//PARS_WARN("don't support files with this extesion yet [" + filePath + "]");
					break;
				}
			}
		}
	}

	const std::set<SPtr<Asset>, AssetCompare>& AssetStore::GetAssets(AssetType type) const
	{
		return m_SortedAssets.at(type);
	}

	Contents AssetStore::GetFolderInDirectory(const std::string& directory)
	{
		std::vector<std::filesystem::directory_entry> files;

		for (const auto& file : std::filesystem::directory_iterator(directory))
		{
			if (file.is_directory())
				files.push_back(file);
		}

		return files;
	}

	std::set<SPtr<Asset>, AssetCompare> AssetStore::GetAssetsOfDirectory(const std::string& path) const
	{
		std::set<SPtr<Asset>, AssetCompare> result;

		for (const auto& [type, loadContent]: m_LoadedContents)
		{
			for (const auto& [originalPath, assetInfos] : loadContent)
			{
				if (path == FILEHELP::GetParentPathFromPath(originalPath))
				{
					result.insert(assetInfos.cbegin(), assetInfos.cend());
				}
			}
		}

		return result;
	}

	SPtr<Asset> AssetStore::GetAsset(AssetType type, const std::string& path) const
	{
		const auto& assetCache = m_AssetCaches.at(type);
		auto iter = assetCache.find(path);
		if (iter != assetCache.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	void AssetStore::SaveAsset(AssetType type, const std::string& path, const std::string& realPath,
		const std::string& extension, const SPtr<Asset>& asset)
	{
		asset->SetFilePath(realPath);
		asset->SetExtension(extension);
		m_AssetCaches[type].emplace(realPath, asset);
		m_SortedAssets[type].emplace(asset);
		m_LoadedContents[type][path].emplace(asset);
	}

	SPtr<Mesh> AssetStore::GetMesh(const std::string& path) const
	{
		return std::reinterpret_pointer_cast<Mesh>(GetAsset(AssetType::StaticMesh, path));
	}

	void AssetStore::LoadMesh(const std::string& path)
	{
		std::string extension = FILEHELP::GetExtentionFromPath(path);
		if (extension == ".obj")
		{
			std::string parentPath = FILEHELP::GetParentPathFromPath(path);
			const auto& meshes = OBJ::LoadObj(path, parentPath);

			for (const SPtr<MaterialMesh>& mesh : meshes)
			{
				std::string realPath = parentPath + "\\" + mesh->GetName();
				SaveAsset(AssetType::StaticMesh, path, realPath, extension, mesh);
			}
		}
	}

	SPtr<Material> AssetStore::GetMaterial(const std::string& path) const
	{
		return std::reinterpret_pointer_cast<Material>(GetAsset(AssetType::Material, path));
	}

	void AssetStore::LoadMaterial(const std::string& path)
	{
		std::string extension = FILEHELP::GetExtentionFromPath(path);
		if (extension == ".mtl")
		{
			std::string parentPath = FILEHELP::GetParentPathFromPath(path);
			const auto& materials = MTL::LoadMtl(path);

			for (const SPtr<Material>& material : materials)
			{
				std::string realPath = parentPath + "\\" + material->GetName();
				SaveAsset(AssetType::Material, path, realPath, extension, material);
			}
		}
	}

	void AssetStore::OnAllMaterialAssetExecuteFunction(std::function<void(const SPtr<Material>& material)> function)
	{
		for (const auto& [path, material] : m_AssetCaches[AssetType::Material])
		{
			//임시로 casting
			function(std::reinterpret_pointer_cast<Material>(material));
		}
	}

	SPtr<Texture> AssetStore::GetTexture(const std::string& path) const
	{
		return std::reinterpret_pointer_cast<Texture>(GetAsset(AssetType::Texture, path));
	}

	void AssetStore::LoadTexture(const std::string& path)
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
				texture->SetFilePath(realPath);
				SaveAsset(AssetType::Texture, path, realPath, extension, texture);
			}
		}
	}

	void AssetStore::OnAllTextureAssetExecuteFunction(std::function<void(const SPtr<Texture>& texture)> function)
	{
		for (const auto& [path, texture] : m_AssetCaches[AssetType::Texture])
		{
			//임시로 casting
			function(std::reinterpret_pointer_cast<Texture>(texture));
		}
	}

	namespace FILEHELP
	{
		std::string GetPathFromFile(const std::filesystem::directory_entry& file)
		{
			return file.path().relative_path().string();
		}

		std::string GetParentPathFromFile(const std::filesystem::directory_entry& file)
		{
			return file.path().parent_path().string();
		}

		std::string GetStemFromFile(const std::filesystem::directory_entry& file)
		{
			return file.path().stem().string();
		}

		std::string GetPathNotExtentionFromFile(const std::filesystem::directory_entry& file)
		{
			std::string path = GetPathFromFile(file);
			std::string extention = GetExtentionFromFile(file);
			return path.substr(0, path.size() - extention.size());
		}

		std::string GetExtentionFromFile(const std::filesystem::directory_entry& file)
		{
			return file.path().extension().string();
		}

		std::string GetExtentionFromPath(std::string path)
		{
			path = path.substr(path.rfind('\\') + 1);
			path = path.substr(path.rfind('.'));
			return path;
		}

		std::string GetStemFromPath(std::string path)
		{
			path = path.substr(path.rfind('\\') + 1);
			path = path.substr(0, path.rfind('.'));
			return path;
		}

		std::string GetParentPathFromPath(std::string path)
		{
			path = path.substr(0, path.rfind('\\'));
			return path;			
		}

		std::string GetNotExtentionFromPath(std::string path)
		{
			std::string extention = GetExtentionFromPath(path);
			return path.substr(0, path.size() - extention.size());
		}

		std::string GetRelativePathFromAbsolute(std::string path)
		{
			std::string curPath =  std::filesystem::current_path().string();
			path = std::string(std::mismatch(path.begin(), path.end(), curPath.begin(), curPath.end()).first, path.end());
			std::replace(path.begin(), path.begin() + path.find_last_of('\\'), '\\', '/');
			return "../" + path;
		}
	}
}
