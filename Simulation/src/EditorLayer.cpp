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
		for (int level = 0; level <= 10; ++level)
		{
			SelectLevel(level);
			m_BasicFuntions.emplace_back([this](int level) {
				ShowLevelHeader(level, m_PhysicsFunctions[level], m_RenderingFunctions[level]);
				});
		}		
	}

	void EditorLayer::Update()
	{
		//ImGui::ShowDemoWindow();

		Vec4 Color;
		ImGui::Begin(m_LayerName.c_str());

		auto index = 0;
		for (const auto& level : m_BasicFuntions)
		{
			level(index++);
		}

		ImGui::End();
	}

	void EditorLayer::SelectLevel(int level)
	{
		switch (level)
		{
		case 0: SetLevel0(); break;
		case 1: SetLevel1(); break;
		case 2: SetLevel2(); break;
		case 3: SetLevel3(); break;
		case 4: SetLevel4(); break;
		case 5: SetLevel5(); break;
		case 6: SetLevel6(); break;
		case 7: SetLevel7(); break;
		case 8: SetLevel8(); break;
		case 9: SetLevel9(); break;
		case 10: SetLevel10(); break;
		}
	}

	void EditorLayer::SetLevel0()
	{
		m_RenderingFunctions[0].emplace_back([this]() {ShowSimulationNode<ClearColorLevel>
			("You can change the background color of the window"); 
			});
	}

	void EditorLayer::SetLevel1()
	{
		m_RenderingFunctions[1].emplace_back([this]() {ShowSimulationNode<DrawTriangleLevel>
			("You can change the position of the vertex",
			"You can change the color of the vertex");
			});

		m_RenderingFunctions[1].emplace_back([this]() {ShowSimulationNode<Camera2DLevel>
			("You can change the position of the rectangle");
			});
	}

	void EditorLayer::SetLevel2()
	{
	}

	void EditorLayer::SetLevel3()
	{
	}

	void EditorLayer::SetLevel4()
	{
	}

	void EditorLayer::SetLevel5()
	{
	}

	void EditorLayer::SetLevel6()
	{
	}

	void EditorLayer::SetLevel7()
	{
	}

	void EditorLayer::SetLevel8()
	{
	}

	void EditorLayer::SetLevel9()
	{
	}

	void EditorLayer::SetLevel10()
	{
	}


	void EditorLayer::ShowLevelHeader(int level, FList& physics, FList& rendering)
	{
		std::string levelName = "Level" + std::to_string(level);
		if (ImGui::CollapsingHeader(levelName.c_str()))
		{
			std::string physicsName = "Physics_" + std::to_string(level);
			std::string renderingName = "Rendering_" + std::to_string(level);
			ShowListNode(physicsName.c_str(), physics);
			ShowListNode(renderingName.c_str(), rendering);
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
}
