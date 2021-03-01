#include "LoadObjLayer.h"
#include "PARS/Component/Render/MeshComponent.h"

namespace PARS
{
	LoadObjLayer::LoadObjLayer()
		: BasicLayer("Load OBJ Layer")
	{
	}

	void LoadObjLayer::Initialize()
	{
		AddDetailFunction("Obj", "MeshComponent", [this]() {ObjDetail(); });
	}

	void LoadObjLayer::ObjDetail()
	{
		static std::string selectObj = "Box";
		static bool IsChangeObj = false;
		
		if (ImGui::Button("Select Default Obj.."))
		{
			ImGui::OpenPopup("Default Obj Popup");
		}

		if (ImGui::BeginPopup("Default Obj Popup"))
		{
			static std::array<std::string, 6> objNames = { "Box", "pyramid", "Slinder", "Sphere", "Tree", "Police" };

			ImGui::Text("Default Obj");
			ImGui::Separator();
			for (const auto objName : objNames)
			{
				if (ImGui::Selectable(objName.c_str()))
				{
					selectObj = objName;
					IsChangeObj = true;
				}
			}
			ImGui::EndPopup();
		}
		ImGui::Separator();

		static char buffer[32] = "";
		ImGui::InputText("Obj File Name", buffer, 32);
		if (ImGui::Button("Change to Input Obj File"))
		{
			selectObj = buffer;
			IsChangeObj = true;
		}

		ImGui::Text("Select Obj : ");
		ImGui::SameLine();
		ImGui::Text(selectObj.c_str());


		if (IsChangeObj)
		{
			if (m_MeshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, std::move(selectObj)))
			{
				selectObj.clear();
			}
			IsChangeObj = false;
		}
	}
}
