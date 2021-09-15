#pragma once
#include "PARS/Core/Core.h"
#include "PARS/Layer/EngineLayer/DetailWindow/Core/DetailWindow.h"

namespace PARS
{
	enum class AssetType
	{
		StaticMesh,
		Material,
		Texture,

	};

	struct AssetInfo
	{
		std::string name;
		std::string path;
		std::string extension;

		friend bool operator<(const AssetInfo& lhs, const AssetInfo& rhs)
		{
			if (lhs.name != rhs.name)
				return lhs.name < rhs.name;
			else
				return lhs.path < rhs.path;
		}
	};

	class Asset
	{
	public:
		Asset() = default;
		virtual ~Asset() = default;

		virtual void Shutdown() {}

		//Please Call these functions in AssetStore/ContentLayer/DetailFunctions..
		virtual void ProcessInputDetailWindow() {}
		virtual void UpdateDetailWindow() {}
		virtual void OpenDetailWindow() {}
		virtual void CloseDetailWindow() {}

	protected:
		AssetInfo m_AssetInfo;

		UPtr<DetailWindow> m_DetailWindow;

	public:
		void SetAssetInfo(const AssetInfo& info) { m_AssetInfo = info; }
		const AssetInfo& GetAssetInfo() const { return m_AssetInfo; }
		void SetName(const std::string& name) { m_AssetInfo.name = name; }
		const std::string& GetName() const { return m_AssetInfo.name; }
		void SetFilePath(const std::string& path) { m_AssetInfo.path = path; }
		const std::string& GetFilePath() const { return m_AssetInfo.path; }
		void SetExtension(const std::string& extension) { m_AssetInfo.extension = extension; }
		const std::string& GetExtension() const { return m_AssetInfo.extension; }
	};

	struct AssetCompare
	{
		bool operator()(const SPtr<Asset>& lhs, const SPtr<Asset>& rhs) const
		{
			return lhs->GetAssetInfo() < rhs->GetAssetInfo();
		}
	};


	using AssetCache = std::unordered_map<std::string, SPtr<Asset>>;
	using LoadContent = std::unordered_map<std::string, std::set<SPtr<Asset>>>;	// originalPath, AssetInfoµé
}


