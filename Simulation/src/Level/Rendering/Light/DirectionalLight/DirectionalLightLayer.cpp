#include "DirectionalLightLayer.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	DirectionalLightLayer::DirectionalLightLayer()
		: BasicLayer("Directional Light Layer")
	{
	}

	void DirectionalLightLayer::Initialize()
	{
		AddDetailFunction("Obj", "MeshComponent", [this]() {ObjDetail(); });
		AddDetailFunction("Light", "Light Actor", [this]() {DirectionalLightDetail(); });
	}

	void DirectionalLightLayer::ObjDetail()
	{
		static std::string selectObj = "Box";
		static bool IsChangeObj = false;
		
		if (ImGui::Button("Select Default Obj.."))
		{
			ImGui::OpenPopup("Default Obj Popup");
		}

		if (ImGui::BeginPopup("Default Obj Popup"))
		{
			static std::array<std::string, 6> objNames = { "Box", "pyramid", "Cylinder", "Sphere", "Tree", "Police" };

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

		ImGui::Text("Select Obj :");
		ImGui::SameLine();
		ImGui::Text(selectObj.c_str());


		if (IsChangeObj)
		{
			if (!m_MeshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, std::move("DirectionalLight/" + selectObj)))
			{
				selectObj.clear();
			}
			IsChangeObj = false;
		}
	}

	void DirectionalLightLayer::DirectionalLightDetail()
	{
		Vec3 m_LightColor;
		ImGui::ColorEdit3("Light Color", (float*)&m_LightColor);

		/*m_LightComp->->SetHandMadeMesh<DiffuseMesh>(
			std::vector<DiffuseVertex>({ {Vec3(-200.0f, 200.0f, 0.0f), Vec4(m_MeshColor)},
				{Vec3(200.0f, 200.0f, 0.0f), Vec4(m_MeshColor)},
				{Vec3(200.0f, -200.0f, 0.0f), Vec4(m_MeshColor)},
				{Vec3(-200.0f, -200.0f, 0.0f), Vec4(m_MeshColor)} }),
			std::vector<UINT>({ 0,1,2,0,2,3 })
			);*/
	}
}
