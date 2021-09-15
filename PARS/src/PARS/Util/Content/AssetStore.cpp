#include "stdafx.h"
#include "PARS/Util/Content/AssetStore.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	AssetStore* AssetStore::s_Instance = nullptr;

	AssetStore::AssetStore()
	{
		s_Instance = this;

		m_GraphicsAssetStore = CreateUPtr<GraphicsAssetStore>();
		m_GraphicsAssetStore->Initialize();

		GetContents(ENGINE_CONTENT_DIR);
		ReloadContents();
	}

	void AssetStore::Shutdown()
	{
		m_GraphicsAssetStore->Shutdown();
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
					if(m_LoadedContents[AssetType::StaticMesh].find(filePath) == m_LoadedContents[AssetType::StaticMesh].cend())
						m_GraphicsAssetStore->LoadMesh(m_ContentsInfos[AssetType::StaticMesh],
							m_LoadedContents[AssetType::StaticMesh], filePath);
					break;
				case HashCode(".mtl"):
					if (m_LoadedContents[AssetType::Material].find(filePath) == m_LoadedContents[AssetType::Material].cend())
						m_GraphicsAssetStore->LoadMaterial(m_ContentsInfos[AssetType::Material], 
							m_LoadedContents[AssetType::Material], filePath);
					break;
				case HashCode(".dds"):
					if (m_LoadedContents[AssetType::Texture].find(filePath) == m_LoadedContents[AssetType::Texture].cend())
						m_GraphicsAssetStore->LoadTexture(m_ContentsInfos[AssetType::Texture], 
							m_LoadedContents[AssetType::Texture], filePath);
					break;
				default:
					//PARS_WARN("don't support files with this extesion yet [" + filePath + "]");
					break;
				}
			}
		}
	}

	const std::set<ContentInfo>& AssetStore::GetContentInfos(AssetType type) const
	{
		return m_ContentsInfos.at(type);
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

	std::set<ContentInfo> AssetStore::GetContentsOfDirectory(const std::string& path) const
	{
		std::set<ContentInfo> result;

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
