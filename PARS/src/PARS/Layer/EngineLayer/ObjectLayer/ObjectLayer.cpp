#include "stdafx.h"
#include "PARS/Layer/LayerManager.h"
#include "PARS/Layer/EngineLayer/ObjectLayer/ObjectLayer.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailLayer.h"
#include "PARS/Layer/EngineLayer/LayerHelper.h"
#include "PARS/Actor/Actor.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	ObjectLayer::ObjectLayer(const std::string& name)
		: Layer(name)
	{
	}

	void ObjectLayer::Update()
	{
		static ImGuiWindowFlags objectsFlags = ImGuiWindowFlags_NoScrollbar;
		ImGui::Begin(m_LayerName.c_str(), nullptr);

		ImVec4 rect = IMGUIHELP::GetImGuiWindowBoxSize();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		if (ImGui::BeginChild("ObjectsChild", ImVec2(rect.z, rect.w), true, objectsFlags))
		{
			UpdateObjects();
			ImGui::EndChild();
			ImGui::PopStyleVar();
		}
		ImGui::End();
	}

	void ObjectLayer::UpdateObjects()
	{
		for (const auto& actor : m_DetailActors)
		{
			if (ImGui::Selectable(actor.second->GetActorName().c_str(), m_SelectActorName == actor.second->GetActorName()))
			{
				m_SelectActorName = actor.second->GetActorName();
				m_SelectActor = actor.second;

				const auto& detailLayer = std::reinterpret_pointer_cast<ActorDetailLayer>(LayerManager::GetLayerManager()->GetLayerByName("Actor Detail Layer"));
				if (detailLayer != nullptr)
				{
					detailLayer->AddSelectActor(m_SelectActor);
				}
			}
		}
	}

	void ObjectLayer::AddActorToLayer(const SPtr<Actor>& actor)
	{
		m_DetailActors.insert({ actor->GetActorName(), actor });
	}

	void ObjectLayer::RemoveActorToLayer(const std::string& name)
	{
		m_DetailActors.erase(name);
		if (name == m_SelectActorName)
		{
			m_SelectActorName = "";
			m_SelectActor = nullptr;
		}
	}


}
