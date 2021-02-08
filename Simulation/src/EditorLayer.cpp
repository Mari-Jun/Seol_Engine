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
		
	}

	void EditorLayer::Update()
	{
		//ImGui::ShowDemoWindow();

		Vec4 Color;
		ImGui::Begin(m_LayerName.c_str());

		ShowLevel0();
		
		ImGui::End();
	}

	void EditorLayer::ShowLevel0()
	{
		FList physics;
		FList rendering;

		rendering.emplace_back([this]() {ShowSimulationNode(CreateSPtr<ClearColorLevel>(), "Change the background color of the window"); });

		ShowLevelHeader("Level0", physics, rendering);

	}

	void EditorLayer::ShowLevelHeader(const char* levelName, FList& physics, FList& rendering)
	{
		if (ImGui::CollapsingHeader(levelName))
		{
			ShowListNode("Physics", physics);
			ShowListNode("Rendering", rendering);
		}
	}

	void EditorLayer::ShowListNode(const char* nodeName, FList& functions)
	{
		if (ImGui::TreeNode(nodeName))
		{
			ImGui::BeginChild(nodeName, ImVec2(0, 260), true);
			for (const auto& function : functions)
			{
				function();
				ImGui::Separator();
			}
			ImGui::EndChild();
			ImGui::TreePop();
		}
	}

	void EditorLayer::ShowSimulationNode(SPtr<Level>&& newLevel, const char* explaination)
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), newLevel->GetLevelName().c_str());
		ImGui::Text(explaination);
		if (ImGui::Button("Start Simulation", ImVec2(-FLT_MIN, 0)))
		{
			AddLevel(newLevel);
		}
	}
}
