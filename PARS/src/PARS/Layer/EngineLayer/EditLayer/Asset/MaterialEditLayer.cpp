#include "stdafx.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailLayer.h"
#include "PARS/Layer/EngineLayer/EditLayer/Asset/MaterialEditLayer.h"
#include "PARS/Component/Render/Material/Material.h"

namespace PARS
{
	MaterialEditLayer::MaterialEditLayer(const std::string& name, const WPtr<Material> material)
		: EditLayer(name)
		, m_Material(material)
	{
	}

	void MaterialEditLayer::Initialize()
	{
		if (!m_Material.expired())
		{
			AddLayer(CreateSPtr<AssetDetailLayer>(m_Material));
		}
	}

	void MaterialEditLayer::UpdateEditLayer()
	{
		if (m_IsFirstOpen)
		{
			m_IsFirstOpen = false;

			ImGui::DockBuilderRemoveNode(m_DockSpaceID);
			ImGui::DockBuilderAddNode(m_DockSpaceID, ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(m_DockSpaceID, ImVec2(m_WindowBoxRect.z, m_WindowBoxRect.w));

			auto dockIDRight = ImGui::DockBuilderSplitNode(m_DockSpaceID, ImGuiDir_Right, 0.2f, nullptr, &m_DockSpaceID);

			ImGui::DockBuilderDockWindow(("Detail##" + m_Material.lock()->GetFilePath()).c_str(), dockIDRight);
			ImGui::DockBuilderFinish(m_DockSpaceID);
		}
	}
}
