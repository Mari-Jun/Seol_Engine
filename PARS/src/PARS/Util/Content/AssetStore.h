#pragma once
#include "PARS/Util/Content/Asset.h"

namespace PARS
{
	constexpr unsigned int HashCode(const char* str)
	{
		return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
	}

	using Contents = std::vector<std::filesystem::directory_entry>;

	class Mesh;
	class Material;
	class Texture;

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
		void PrepareToNextDraw();

		void ReloadContents();

	private:
		void GetContents(const std::string& rootPath);

	private:
		std::unordered_map<AssetType, AssetCache> m_AssetCaches;
		std::map<AssetType, std::set<SPtr<Asset>, AssetCompare>> m_SortedAssets;
		std::map<AssetType, LoadContent> m_LoadedContents; //.PARS로 따로 관리하기 전에는 이렇게 관리해 줘야 할 것 같다. 따라서 현재 느린것은 감당해야할듯?
		std::map<AssetType, bool> m_IsAddedNewItems;

	public:
		const std::set<SPtr<Asset>, AssetCompare>& GetAssets(AssetType type) const;
		Contents GetFolderInDirectory(const std::string& directory);
		std::set<SPtr<Asset>, AssetCompare> GetAssetsOfDirectory(const std::string& path) const;
		bool IsAddedNewItemForType(AssetType type);

	private:
		UINT GetAssetCount(AssetType type) const { return static_cast<UINT>(m_AssetCaches.at(type).size()); }
		SPtr<Asset> GetAsset(AssetType type, const std::string& path) const;
		void SaveAsset(AssetType type, const std::string& path, const std::string& realPath,
			const std::string& extension, const SPtr<Asset>& asset);

	public:
		UINT GetMeshAssetCount() const { return GetAssetCount(AssetType::StaticMesh); }
		SPtr<Mesh> GetMesh(const std::string& path) const; 
		void LoadMesh(const std::string& path);

		UINT GetMaterialAssetCount() const { return GetAssetCount(AssetType::Material); }
		SPtr<Material> GetMaterial(const std::string& path) const;
		void LoadMaterial(const std::string& path);
		void OnAllMaterialAssetExecuteFunction(std::function<void(const SPtr<Material>& material)> function);

		UINT GetTextureAssetCount() const { return GetAssetCount(AssetType::Texture); }
		SPtr<Texture> GetTexture(const std::string& path) const;
		void LoadTexture(const std::string& path);
		void OnAllTextureAssetExecuteFunction(std::function<void(const SPtr<Texture>& texture)> function);
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


