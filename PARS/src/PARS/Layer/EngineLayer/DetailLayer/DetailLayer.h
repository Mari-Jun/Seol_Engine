#pragma once
#include "PARS/Layer/Layer.h"
#include "imgui.h"

namespace PARS
{
	class Actor;
	class Asset;
	class Level;
	struct DetailInfo;

	class DetailLayer : public Layer
	{
	public:
		DetailLayer(const std::string& layerName, const std::string& windowName);
		virtual ~DetailLayer() = default;

		virtual void Update() override final;

	private:
		virtual void UpdateDetail() {}

	protected:
		void UpdateDetailInfo(const DetailInfo& info);

	protected:
		ImGuiWindowFlags m_WindowFlags = 0;
		std::string m_WindowName;

	public:
		const std::string& GetWindowName() const { return m_WindowName; }
	};

	class ActorDetailLayer : public DetailLayer
	{
	public:
		ActorDetailLayer(const std::string& name = "Actor Detail Layer");
		ActorDetailLayer(const WPtr<Actor>& actor);
		virtual ~ActorDetailLayer() = default;

	private:
		virtual void UpdateDetail() override;

	public:
		void AddSelectActor(const WPtr<Actor>& actor);

	private:
		WPtr<Actor> m_SelectActor;
	};

	class AssetDetailLayer : public DetailLayer
	{
	public:
		AssetDetailLayer(const WPtr<Asset>& asset);
		virtual ~AssetDetailLayer() = default;

	private:
		virtual void UpdateDetail() override;

	public:
		void AddSelectAsset(const WPtr<Asset>& asset);

	private:
		WPtr<Asset> m_Asset;
	};

	class LevelDetailLayer : public DetailLayer
	{
	public:
		LevelDetailLayer(const std::string& name = "Level Detail Layer");
		virtual ~LevelDetailLayer() = default;

	private:
		virtual void UpdateDetail() override;

	public:
		void AddSelectLevel(const WPtr<Level>& level);

	private:
		WPtr<Level> m_Level;
	};


}


