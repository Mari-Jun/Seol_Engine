#include "stdafx.h"
#include "PARS/Layer/EngineLayer/InterfaceLayer/InterfaceLayer.h"
#include "PARS/Level/LevelManager.h"

namespace PARS
{
	InterfaceLayer::InterfaceLayer(const std::string& name)
		: Layer(name)
	{
	}

	void InterfaceLayer::Update()
	{
		if (ImGui::Begin(m_LayerName.c_str(), nullptr, m_WindowFlags))
		{
			if (ImGui::Button("Start"))
			{
				LevelManager::GetLevelManager()->StartOpenedLevel();
			}

			if (ImGui::Button("Stop"))
			{
				LevelManager::GetLevelManager()->StopOpenedLevel();
			}

			if (ImGui::Button("Save"))
			{
				LevelManager::GetLevelManager()->SaveOpenedLevel();
			}
		}
		ImGui::End();
	}
}
