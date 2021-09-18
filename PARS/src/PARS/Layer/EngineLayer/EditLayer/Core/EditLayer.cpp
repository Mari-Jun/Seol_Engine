#include "stdafx.h"
#include "PARS/Layer/EngineLayer/EditLayer/Core/EditLayer.h"

namespace PARS
{
	EditLayer::EditLayer(const std::string& name)
		: Layer(name)
	{
		//m_DockWindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
		m_DockWindowFlags = ImGuiWindowFlags_None;
	}

	void EditLayer::Shutdown()
	{
		for (const auto& layer : m_Layers)
			layer.lock()->SetLayerState(LayerState::Dead);
		m_Layers.clear();
	}

	void EditLayer::Update()
	{
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoDockingInCentralNode;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_FirstUseEver);
		ImGui::Begin(m_LayerName.c_str(), &m_IsOpen, window_flags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);

		m_WindowBoxRect = IMGUIHELP::GetImGuiWindowBoxSize();

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			m_DockSpaceID = ImGui::GetID(m_LayerName.c_str());
			ImGui::DockSpace(m_DockSpaceID, ImVec2(0.0f, 0.0f), dockspace_flags);

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Options"))
				{
					//// Disabling fullscreen would allow the window to be moved to the front of other windows,
					//// which we can't undo at the moment without finer window depth/z control.
					//if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
					//if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
					//if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
					//if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
					//ImGui::Separator();

					//if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
					//	*p_open = false;
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

		}
		ImGui::End();

		UpdateEditLayer();

		if (m_IsOpen == false)
			SetLayerState(LayerState::Dead);
	}

	void EditLayer::AddLayer(const SPtr<Layer>& layer)
	{
		Layer::AddLayer(layer);
		m_Layers.push_back(layer);
	}

}