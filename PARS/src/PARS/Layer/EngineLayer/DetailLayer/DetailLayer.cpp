#include "stdafx.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailLayer.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunction.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/Core/Renderer.h"
#include "PARS/Actor/Actor.h"

//юс╫ц
#include "PARS/Level/LevelManager.h"

namespace PARS
{
	DetailLayer::DetailLayer(const std::string& name)
		: Layer(name)
	{
	}

	void DetailLayer::Update()
	{
		ImGui::Begin(m_LayerName.c_str(), nullptr, m_WindowFlags);
		{
			{
				static ImGuiWindowFlags objectsFlags = ImGuiWindowFlags_NoScrollbar;
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("ObjectsChild", ImVec2(m_WindowSize.x - 30.0f, m_WindowSize.y * 0.25f), true, objectsFlags);
				if (ImGui::BeginTabBar("Objects Tab"))
				{
					if (ImGui::BeginTabItem("Objects"))
					{
						UpdateObjects();
						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
				ImGui::EndChild();
				ImGui::PopStyleVar();
			}

			{
				static ImGuiWindowFlags detailFlags = ImGuiWindowFlags_NoScrollbar;
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild("DetailChild", ImVec2(m_WindowSize.x - 30.0f, m_WindowSize.y * 0.69f), true, detailFlags);
				if (ImGui::BeginTabBar("Detail Tab"))
				{
					if (ImGui::BeginTabItem("Detail"))
					{
						UpdateDetail();
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem(m_Level.expired() ? "Level Setting" : (m_Level.lock()->GetLevelName() + " Setting").c_str()))
					{
						UpdateLevelSetting();
						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
				ImGui::EndChild();
				ImGui::PopStyleVar();
			}
		}
		m_WindowSize = ImGui::GetWindowSize();
		ImGui::End();
	

		if (!m_IsOpen)
		{
			//Destroy();
		}
	}

	void DetailLayer::Shutdown()
	{
		//f_Destroy();
	}

	void DetailLayer::UpdateObjects()
	{
		for (const auto& actor : m_DetailActors)
		{
			if (ImGui::Selectable(actor.second->GetActorName().c_str(), m_SelectActorName == actor.second->GetActorName()))
			{
				m_SelectActorName = actor.second->GetActorName();
				m_SelectActor = actor.second;
			}
		}
	}

	void DetailLayer::UpdateDetail()
	{
		if (m_SelectActor != nullptr)
		{
			m_SelectActor->OnUpdateDetailInfo([this](const DetailInfo& info) {
				UpdateDetailInfo(info);
				});
		}
	}

	void DetailLayer::UpdateLevelSetting()
	{
		if (!m_Level.expired())
		{
			m_Level.lock()->OnUpdateDetailInfo([this](const DetailInfo& info) {
				UpdateDetailInfo(info);
				});
		}
	}

	void DetailLayer::UpdateDetailInfo(const DetailInfo& info)
	{
		if (info.state != DVS::Hide && info.state != DVS::HideAll &&
			ImGui::CollapsingHeader(info.headerName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (const auto& [name, function, isDefault, fState] : info.functionInfos)
			{
				if (fState != FVS::Hide && (info.state != DVS::HideDefault || !isDefault)
					&& ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Separator();
					if (fState == FVS::Disabled)
					{
						ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
						ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
					}
					function();
					if (fState == FVS::Disabled)
					{
						ImGui::PopStyleVar();
						ImGui::PopItemFlag();
					}
					ImGui::Separator();
					ImGui::TreePop();
				}
			}
		}
	}

	void DetailLayer::AddActorToLayer(const SPtr<Actor>& actor)
	{
		m_DetailActors.insert({ actor->GetActorName(), actor });
	}

	void DetailLayer::RemoveActorToLayer(const std::string& name)
	{
		m_DetailActors.erase(name);
		if (name == m_SelectActorName)
		{
			m_SelectActorName = "";
			m_SelectActor = nullptr;
		}
	}

	void DetailLayer::SetLevelToLayer(const WPtr<Level>& level)
	{
		m_Level = level;
	}
}