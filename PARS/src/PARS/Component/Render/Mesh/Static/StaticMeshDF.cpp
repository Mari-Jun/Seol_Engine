#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshDF.h"
#include "PARS/Util/Helper/ContentHelper.h"

namespace PARS
{
	void StaticMeshCompDetailFunction::CreateFunctionInfos()
	{
		MeshCompDetailFunction::CreateFunctionInfos();

		const auto& comp = std::reinterpret_pointer_cast<StaticMeshComponent>(m_Component.lock());
		if (comp != nullptr)
		{
			comp->AddDetailFunctionInfo(FunctionInfo{ "Set Mesh", [this, comp]() { SetMeshDetail(comp); } });
		}
	}

	void StaticMeshCompDetailFunction::SetMeshDetail(const SPtr<StaticMeshComponent>& meshComp)
	{
		std::filesystem::directory_entry selectFile;

		if (ImGui::BeginCombo("Static Mesh", meshComp->GetMesh()->GetFileName().c_str(),
			ImGuiComboFlags_PopupAlignLeft | ImGuiComboFlags_HeightRegular))
		{
			int cnt = 0;
			for (const auto& file : ContentHelper::GetStaticMeshContents())
			{
				std::string stemName = file.path().stem().u8string();
				std::string fileName = file.path().filename().u8string();
				std::string path = file.path().relative_path().u8string();

				if (ImGui::Selectable((stemName + "##" + std::to_string(cnt++)).c_str()))
				{
					selectFile = file;
				}

				ContentHelper::ShowItemInfo({ path });
			}
			ImGui::EndCombo();
		}

		if (selectFile.exists())
		{
			meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, selectFile.path().relative_path().u8string());
		}
	}
}