#pragma once
#include "PARS/Util/Content/GraphicsAssetStore.h"

namespace PARS
{
	using Contents = std::vector<std::filesystem::directory_entry>;

	class AssetStore
	{
	private:
		static AssetStore* s_Instance;

	public:
		inline static AssetStore* GetAssetStore() { return s_Instance; }

	public:
		AssetStore();
		virtual ~AssetStore() = default;

		void Shutdown();
		void Update();

		void ReloadContents();

		Contents GetContentsInDirectory(const std::string& directory,
			const std::initializer_list<std::string>& filter, const std::initializer_list<std::string>& antiFilter);
	
		void ShowItemInfo(std::initializer_list<std::string>&& texts);

		std::string GetPathFromFile(const std::filesystem::directory_entry& file);
		std::string GetParentPathFromFile(const std::filesystem::directory_entry& file);
		std::string GetStemFromFile(const std::filesystem::directory_entry& file);
		std::string GetPathNotExtentionFromFile(const std::filesystem::directory_entry& file);
		std::string GetExtentionFromFile(const std::filesystem::directory_entry& file);
		std::string GetFileNameFromPath(std::string path);

		const Contents& GetStaticMeshContents() { return m_StaticMeshContents; }

	private:
		void GetDirectorys(const std::filesystem::path& path);
		void GetContents(Contents& contents, const std::initializer_list<std::string>& filter, const std::initializer_list<std::string>& antiFilter);

	private:
		std::vector<std::string> m_DirectoryPaths;
		Contents m_StaticMeshContents;
		Contents m_MaterialContents;

		SPtr<GraphicsAssetStore> m_GraphicsAssetStore;
	};
}


