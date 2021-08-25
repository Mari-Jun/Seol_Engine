#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshDF.h"

namespace PARS
{
	void HandmadeMeshCompDetailFunction::CreateFunctionInfos()
	{
		MeshCompDetailFunction::CreateFunctionInfos();

		const auto& comp = std::reinterpret_pointer_cast<HandmadeMeshComponent>(m_Component.lock());
		if (comp != nullptr)
		{
			comp->AddDetailFunctionInfo(FunctionInfo{ "VertexInfo", [this, comp]() { VertexInfoDetail(comp); } });
		}
	}

	void HandmadeMeshCompDetailFunction::VertexInfoDetail(const SPtr<HandmadeMeshComponent>& meshComp)
	{
		const auto& mesh = meshComp->GetMesh();
		
		const auto& diffuseMesh = std::reinterpret_pointer_cast<DiffuseMesh>(mesh);
		if (diffuseMesh != nullptr)
		{
			auto& vertices = diffuseMesh->GetDiffseVertices();
			Vec3 pos;
			Vec4 color;
			for (int i = 0; i < vertices.size(); ++i)
			{
				pos = vertices[i].GetPosition();
				ImGui::DragFloat3(("Position" + std::to_string(i + 1)).c_str(), (float*)&pos, 0.5f, -FLT_MAX, FLT_MAX, "%.4f");

				color = vertices[i].GetDiffuseColor();
				ImGui::ColorEdit4(("Color" + std::to_string(i + 1)).c_str(), (float*)&color);

				if (vertices[i].GetPosition() != pos || vertices[i].GetDiffuseColor() != color)
				{
					vertices[i].SetPosition(pos);
					vertices[i].SetDiffuseColor(color);
					meshComp->SetRenderState(RenderState::Changed);
				}
			}
		}
	}
}
