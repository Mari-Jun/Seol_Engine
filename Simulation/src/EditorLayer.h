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
		void SetAlgorithm();
		void SetMathematics();

		void ShowLevelHeader(std::string_view subtitle, std::map<std::string_view, FList> subjects);
		void ShowListNode(const char* nodeName, FList& functions);

		template<typename T>
		void ShowSimulationNode(const std::string& levelNum, std::initializer_list<std::string>&& args)
		{
			auto newLevel = CreateSPtr<T>();

			std::string nodeName = "No." + levelNum + " [" + newLevel->GetLevelName() + "]";

			ImGui::TextColored(ImVec4(1, 1, 0, 1), nodeName.c_str());

			size_t size = Math::Min<size_t>(args.size(), 5);

			ImGuiStyle& style = ImGui::GetStyle();
			float childHeight = ImGui::GetTextLineHeight() * size + style.ItemSpacing.y * (size - 1) + 
				style.ScrollbarSize + style.WindowPadding.y * 2.0f;
			ImGui::BeginChild(nodeName.c_str(), ImVec2(0, childHeight), true, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			for (const auto& text : args)
			{
				ImGui::BulletText(text.c_str());
			}
			ImGui::PopStyleVar();
			ImGui::EndChild();

			if (ImGui::Button(("Start Simulation!##" + levelNum).c_str(), ImVec2(-FLT_MIN, 0)))
			{
				AddLevel(newLevel);
			}
		}

	private:
		FLevelList m_BasicFuntions;
		std::map<std::string_view, FList> m_PhysicsSubjects;
		std::map<std::string_view, FList> m_RenderingSubjects;
		std::map<std::string_view, FList> m_AlgorithmSubjects;
		std::map<std::string_view, FList> m_MathematicsSubjects;
	};
}