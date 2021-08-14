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
		bool* p_open = false;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}


		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
					*p_open = false;
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::End();


		ImGui::ShowDemoWindow();

		Vec4 Color;
		ImGui::Begin(m_LayerName.c_str());

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
		m_RenderingSubjects["R_Basic"].emplace_back([this]() {ShowSimulationNode<ClearColorLevel>
			("001", "You can change the background color of the window");
			});

		m_RenderingSubjects["R_Mesh"].emplace_back([this]() {ShowSimulationNode<DrawTriangleLevel>
			("002", "You can change the position of the vertex",
				"You can change the color of the vertex");
			});

		m_RenderingSubjects["R_Camera"].emplace_back([this]() {ShowSimulationNode<Camera2DLevel>
			("003", "You can change the position of the rectangle",
				"You can change the color of the rectangle",
				"You can check the position of the rectangle and camera");
			});

		m_RenderingSubjects["R_Mesh"].emplace_back([this]() {ShowSimulationNode<LoadObjLevel>
			("004", "You can change the mesh by loading obj");
			});

		m_RenderingSubjects["R_Light"].emplace_back([this]() {ShowSimulationNode<DirectionalLightLevel>
			("005", "You can change rotation of the directional light",
				"You can change color of the directional light");
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
