#pragma once

#include <PARS.h>

namespace PARS
{
	using FList = std::vector<std::function<void()>>;
	using FLevelList = std::vector<std::function<void()>>;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void Initialize() override;
		void Update() override;

	private:
		void SetPhysics();
		void SetRendering();

		void ShowLevelHeader(std::string_view subtitle, std::map<std::string_view, FList> subjects);
		void ShowListNode(const char* nodeName, FList& functions);

		template<typename... Args>
		void ShowExplanation(const Args&... args)
		{
			(ImGui::BulletText(args), ...);
		}
		template<typename T, typename ... Args>
		void ShowSimulationNode(const std::string& levelNum, Args&& ... args)
		{
			auto newLevel = CreateSPtr<T>();

			std::string nodeName = "No." + levelNum + " [" + newLevel->GetLevelName() + "]";

			ImGui::TextColored(ImVec4(1, 1, 0, 1), nodeName.c_str());

			ShowExplanation(args...);

			static std::string buttonName = "Start " + newLevel->GetLevelName() + " Simulation";

			if (ImGui::Button(buttonName.c_str(), ImVec2(-FLT_MIN, 0)))
			{
				AddLevel(newLevel);
			}
		}
		

	private:
		FLevelList m_BasicFuntions;
		std::map<std::string_view, FList> m_PhysicsSubjects;
		std::map<std::string_view, FList> m_RenderingSubjects;
	};
}