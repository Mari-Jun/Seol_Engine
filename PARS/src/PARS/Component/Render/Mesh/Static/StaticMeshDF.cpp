#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshDF.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Util/Content/AssetStore.h"

namespace PARS
{
	void StaticMeshCompDetailFunction::CreateFunctionInfos()
	{
		MeshCompDetailFunction::CreateFunctionInfos();

		const auto& comp = std::reinterpret_pointer_cast<StaticMeshComponent>(m_Component.lock());
		if (comp != nullptr)
		{
			comp->AddDetailFunctionInfo(FunctionInfo{ "Set Mesh", [this, comp]() { SetMeshDetail(comp); } });
			comp->AddDetailFunctionInfo(FunctionInfo{ "Set Material", [this, comp]() { SetMaterialDetail(comp); } });
		}
	}

	void StaticMeshCompDetailFunction::SetMeshDetail(const SPtr<StaticMeshComponent>& meshComp)
	{
		SPtr<Mesh> selectMesh = nullptr;

		const auto& assetStore = AssetStore::GetAssetStore();

		if (ImGui::BeginCombo("Static Mesh", meshComp->GetMesh()->GetName().c_str(),
			ImGuiComboFlags_PopupAlignLeft | ImGuiComboFlags_HeightRegular))
		{
			int cnt = 0;
			for (const auto& asset : assetStore->GetAssets(AssetType::StaticMesh))
			{
				if(ImGui::Selectable((asset->GetName() + "##" + std::to_string(cnt++)).c_str()))
				{
					selectMesh = std::reinterpret_pointer_cast<Mesh>(asset);
				}
			}
			ImGui::EndCombo();
		}
		else
		{
			IMGUIHELP::ShowAssetPath(meshComp->GetMesh()->GetFilePath().c_str());
		}

		if (selectMesh != nullptr)
		{
			meshComp->SetMesh(selectMesh);
		}
	}

	void StaticMeshCompDetailFunction::SetMaterialDetail(const SPtr<StaticMeshComponent>& meshComp)
	{
		const auto& assetStore = AssetStore::GetAssetStore();

		const auto& materials = meshComp->GetMaterials();

		int index = 0;
		for (auto& material : materials)
		{
			std::string selectPath;
			SPtr<Material> selectMaterial = nullptr;

			if (ImGui::BeginCombo(("Element " + std::to_string(index)).c_str(), material->GetName().c_str(),
				ImGuiComboFlags_PopupAlignLeft | ImGuiComboFlags_HeightRegular))
			{
				int cnt = 0;
				for (const auto& asset : assetStore->GetAssets(AssetType::Material))
				{
					if (ImGui::Selectable((asset->GetName() + "##" + std::to_string(cnt++)).c_str()))
					{
						selectPath = asset->GetFilePath();
						selectMaterial = std::reinterpret_pointer_cast<Material>(asset);
					}
				}
				ImGui::EndCombo();
			}
			else
			{
				IMGUIHELP::ShowAssetPath(material->GetFilePath().c_str());
			}

			if (selectMaterial != nullptr)
				meshComp->SetMaterial(selectMaterial, index);

			++index;
		}

		

	}
}