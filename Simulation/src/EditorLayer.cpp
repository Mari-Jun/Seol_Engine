#include "EditorLayer.h"
#include "LevelHeader.h"
#include <imgui/imgui.h>

namespace PARS
{
	EditorLayer::EditorLayer()
		: Layer("Editor Layer")
	{
		
	}

	void EditorLayer::Initialize()
	{
		SetPhysics();
		m_BasicFuntions.emplace_back([this]() {
			ShowLevelHeader("Physics", m_PhysicsSubjects);
			});

		SetRendering();
		m_BasicFuntions.emplace_back([this]() {
			ShowLevelHeader("Rendering", m_RenderingSubjects);
			});

		SetAlgorithm();
		m_BasicFuntions.emplace_back([this]() {
			ShowLevelHeader("Algorithm", m_AlgorithmSubjects);
			});

		SetMathematics();
		m_BasicFuntions.emplace_back([this]() {
			ShowLevelHeader("Mathematics", m_MathematicsSubjects);
			});
	}

	void EditorLayer::Update()
	{
		ImGui::ShowDemoWindow();

		Vec4 Color;
		ImGui::Begin(m_LayerName.c_str(), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

		auto index = 0;
		for (const auto& level : m_BasicFuntions)
		{
			level();
		}

		ImGui::End();
	}

	void EditorLayer::SetPhysics()
	{
		/*m_PhysicsSubjects["P_Basic"].emplace_back([this]() {ShowSimulationNode<ClearColorLevel>
			("You can change the background color of the window");
			});*/
	}

	void EditorLayer::SetRendering()
	{
		m_RenderingSubjects["R_Light"].emplace_back([this]() {ShowSimulationNode<DirectionalLightLevel>
			("005", 
				{ "You can change rotation of the directional light",
				"You can change color of the directional light" });
			});
	}

	void EditorLayer::SetAlgorithm()
	{
	}

	void EditorLayer::SetMathematics()
	{
	}

	void EditorLayer::ShowLevelHeader(std::string_view subtitle, std::map<std::string_view, FList> subjects)
	{
		if (ImGui::CollapsingHeader(subtitle.data()))
		{
			for (auto [subject, datalist] : subjects)
			{
				ShowListNode(subject.data(), datalist);
			}
		}
	}

	void EditorLayer::ShowListNode(const char* nodeName, FList& functions)
	{
		if (ImGui::TreeNode(nodeName))
		{
			ImGui::BeginChild(nodeName, ImVec2(0, 360), true);
			for (const auto& function : functions)
			{
				function();
				ImGui::Separator();
			}
			ImGui::EndChild();
			ImGui::TreePop();
		}
	}
}
