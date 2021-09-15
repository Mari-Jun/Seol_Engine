#pragma once
#include "PARS/Util/Content/GraphicsAssetStore.h"

namespace PARS
{
	constexpr unsigned int HashCode(const char* str)
	{
		return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
	}

	enum class AssetType
	{
		StaticMesh,
		Material,
		Texture,

	};

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
		void Update(float deltaTime);

		void ReloadContents();

	private:
		void GetContents(const std::string& rootPath);

	private:
		std::map<AssetType, std::set<ContentInfo>> m_ContentsInfos; // [name, path]
		std::map<AssetType, LoadContent> m_LoadedContents; //.PARS로 따로 관리하기 전에는 이렇게 관리해 줘야 할 것 같다. 따라서 현재 느린것은 감당해야할듯?

		SPtr<GraphicsAssetStore> m_GraphicsAssetStore;
	public:
		const std::set<ContentInfo>& GetContentInfos(AssetType type) const;
		Contents GetFolderInDirectory(const std::string& directory);
		std::set<ContentInfo> GetContentsOfDirectory(const std::string& path) const;
	};

	namespace FILEHELP
	{
		std::string GetPathFromFile(const std::filesystem::directory_entry& file);
		std::string GetParentPathFromFile(const std::filesystem::directory_entry& file);
		std::string GetStemFromFile(const std::filesystem::directory_entry& file);
		std::string GetPathNotExtentionFromFile(const std::filesystem::directory_entry& file);
		std::string GetExtentionFromFile(const std::filesystem::directory_entry& file);

		std::string GetExtentionFromPath(std::string path);
		std::string GetStemFromPath(std::string path);
		std::string GetParentPathFromPath(std::string path);
		std::string GetNotExtentionFromPath(std::string path);

		std::string GetRelativePathFromAbsolute(std::string path);
	}
}


