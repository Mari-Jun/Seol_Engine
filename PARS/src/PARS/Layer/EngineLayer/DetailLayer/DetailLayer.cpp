#include "stdafx.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailLayer.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunction.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/Core/Renderer.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Util/Content/Asset.h"

//юс╫ц
#include "PARS/Level/LevelManager.h"

namespace PARS
{
	DetailLayer::DetailLayer(const std::string& layerName, const std::string& windowName)
		: Layer(layerName)
		, m_WindowName(windowName)
	{
	}

	void DetailLayer::Update()
	{
		ImGui::Begin(m_WindowName.c_str(), nullptr, m_WindowFlags);
		{
			{
				ImVec4 rect = IMGUIHELP::GetImGuiWindowBoxSize();

				static ImGuiWindowFlags detailFlags = ImGuiWindowFlags_NoScrollbar;
				ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
				ImGui::BeginChild(("Child " + m_WindowName).c_str(), ImVec2(rect.z, rect.w), true, detailFlags);

				UpdateDetail();

				ImGui::EndChild();
				ImGui::PopStyleVar();
			}
		}

		ImGui::End();
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

	ActorDetailLayer::ActorDetailLayer(const std::string& name)
		: DetailLayer(name, "Detail##WorldActor")
	{
	}

	ActorDetailLayer::ActorDetailLayer(const WPtr<Actor>& actor)
		: DetailLayer("Actor Detail Layer##" + actor.lock()->GetActorName(),
			"Detail##" + actor.lock()->GetActorName())
	{
	}

	void ActorDetailLayer::UpdateDetail()
	{
		if (!m_SelectActor.expired())
		{
			m_SelectActor.lock()->OnUpdateDetailInfo([this](const DetailInfo& info) {
				UpdateDetailInfo(info);
				});
		}
	}

	void ActorDetailLayer::AddSelectActor(const WPtr<Actor>& actor)
	{
		m_SelectActor = actor;
	}

	AssetDetailLayer::AssetDetailLayer(const WPtr<Asset>& asset)
		: DetailLayer("Asset Detail Layer##" + asset.lock()->GetFilePath(),
			"Detail##" + asset.lock()->GetFilePath())
	{
	}

	void AssetDetailLayer::UpdateDetail()
	{
	}

	void AssetDetailLayer::AddSelectAsset(const WPtr<Asset>& asset)
	{
	}

	LevelDetailLayer::LevelDetailLayer(const std::string& name)
		: DetailLayer(name, "World Setting")
	{
	}

	void LevelDetailLayer::UpdateDetail()
	{
		if (!m_Level.expired())
		{
			m_Level.lock()->OnUpdateDetailInfo([this](const DetailInfo& info) {
				UpdateDetailInfo(info);
				});
		}
	}

	void LevelDetailLayer::AddSelectLevel(const WPtr<Level>& level)
	{
		m_Level = level;
	}
}