#pragma once
#include "PARS/Layer/Layer.h"
#include "imgui.h"

namespace PARS
{
	class Actor;
	class Level;
	struct DetailInfo;

	class DetailLayer : public Layer
	{
	public:
		DetailLayer(const std::string& name = "Detail Layer");
		virtual ~DetailLayer() = default;

		virtual void Initialize() override {}
		virtual void Shutdown() override;
		virtual void Update() override final;
		void OnDestroy(std::function<void()> func) { f_Destroy = func; }

	private:
		void UpdateObjects();
		void UpdateDetail();
		void UpdateLevelSetting();
		void UpdateDetailInfo(const DetailInfo& info);
		void UpdateEndMenu();

	public:
		void AddActorToLayer(const SPtr<Actor>& actor);
		void RemoveActorToLayer(const std::string& name);
		void SetLevelToLayer(const WPtr<Level>& level);

	private:
		bool m_IsOpen = true;
		ImGuiWindowFlags m_WindowFlags = 0;
		ImVec2 m_WindowSize;
		ImVec2 m_WindowPos;
		std::function<void()> f_Destroy;

	private:
		std::string m_SelectActorName;
		SPtr<Actor> m_SelectActor;
		std::multimap<std::string, const SPtr<Actor>> m_DetailActors;
		WPtr<Level> m_Level;
	};
}


