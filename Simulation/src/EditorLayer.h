#pragma once

#include <PARS.h>

namespace PARS
{
	using FList = std::vector<std::function<void()>>;
	using FLevelList = std::vector<std::function<void(int level)>>;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		void Initialize() override;
		void Update() override;

	private:
		void SelectLevel(int level);
		void SetLevel0();
		void SetLevel1();
		void SetLevel2();
		void SetLevel3();
		void SetLevel4();
		void SetLevel5();
		void SetLevel6();
		void SetLevel7();
		void SetLevel8();
		void SetLevel9();
		void SetLevel10();

		void ShowLevelHeader(int level, FList& physics, FList& rendering);
		void ShowListNode(const char* nodeName, FList& functions);

		template<typename... Args>
		void ShowExplanation(const Args&... args)
		{
			(ImGui::BulletText(args), ...);
		}
		template<typename T, typename ... Args>
		void ShowSimulationNode(Args&& ... args)
		{
			auto newLevel = CreateSPtr<T>();

			ImGui::TextColored(ImVec4(1, 1, 0, 1), newLevel->GetLevelName().c_str());

			ShowExplanation(args...);

			static std::string buttonName = "Start " + newLevel->GetLevelName() + " Simulation";

			if (ImGui::Button(buttonName.c_str(), ImVec2(-FLT_MIN, 0)))
			{
				AddLevel(newLevel);
			}
		}
		

	private:
		FLevelList m_BasicFuntions;
		std::array<FList, 11> m_PhysicsFunctions;
		std::array<FList, 11> m_RenderingFunctions;

	};
}