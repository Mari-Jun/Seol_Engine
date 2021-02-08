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

		if (ImGui::CollapsingHeader("Level0"))
		{
			if (ImGui::TreeNode("Physics"))
			{
				ImGui::Text("Hello Physics");
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Rendering"))
			{
				if (ImGui::Button("Clear Color1"))
				{
					AddLevel(PARS::CreateSPtr<PARS::ClearColorLevel>());
				}
				ImGui::TreePop();
			}
		}

		ImGui::End();
	}
}
