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
		std::string selectFile;

		const auto& assetStore = AssetStore::GetAssetStore();
		const auto& gAssetStore = GraphicsAssetStore::GetAssetStore();

		if (ImGui::BeginCombo("Static Mesh", meshComp->GetMesh()->GetObjectName().c_str(),
			ImGuiComboFlags_PopupAlignLeft | ImGuiComboFlags_HeightRegular))
		{
			int cnt = 0;
			for (const auto& [name, path] : assetStore->GetContentInfos(AssetType::StaticMesh))
			{
				const auto& mesh = gAssetStore->GetMesh(path);
				if (mesh != nullptr)
				{
					if (ImGui::Selectable((mesh->GetObjectName() + "##" + std::to_string(cnt++)).c_str()))
					{
						selectFile = path;
					}
					assetStore->ShowItemInfo({ path });
				}
			}
			ImGui::EndCombo();
		}

		if (!selectFile.empty())
		{
			meshComp->SetMesh(std::move(selectFile));
		}
	}

	void StaticMeshCompDetailFunction::SetMaterialDetail(const SPtr<StaticMeshComponent>& meshComp)
	{
		const auto& assetStore = AssetStore::GetAssetStore();
		const auto& gAssetStore = GraphicsAssetStore::GetAssetStore();

		const auto& materials = meshComp->GetMaterials();

		int index = 0;
		for (auto& material : materials)
		{
			SPtr<Material> selectMaterial = nullptr;

			if (ImGui::BeginCombo(("Element " + std::to_string(index)).c_str(), material->GetName().c_str(),
				ImGuiComboFlags_PopupAlignLeft | ImGuiComboFlags_HeightRegular))
			{
				int cnt = 0;
				for (const auto& [name, path] : assetStore->GetContentInfos(AssetType::Material))
				{
					const auto& material = gAssetStore->GetMaterial(path);
					if (material != nullptr)
					{
						if (ImGui::Selectable((material->GetName() + "##" + std::to_string(cnt++)).c_str()))
						{
							selectMaterial = material;
						}

						assetStore->ShowItemInfo({ path });
					}
				}
			
				ImGui::EndCombo();
			}

			if (selectMaterial != nullptr)
				meshComp->SetMaterial(selectMaterial, index);

			++index;
		}

		

	}
}