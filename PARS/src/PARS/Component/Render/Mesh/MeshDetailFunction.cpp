#include "stdafx.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Component/Render/Mesh/MeshDetailFunction.h"

namespace PARS
{
	void MeshCompDetailFunction::CreateFunctionInfos()
	{
		const auto& comp = std::reinterpret_pointer_cast<MeshComponent>(m_Component.lock());
		if (comp != nullptr)
		{
			comp->AddDetailFunctionInfo(FunctionInfo{ "MeshCount", [this, comp]() { MeshCountDetail(comp); } });
		}
	}

	void MeshCompDetailFunction::MeshCountDetail(const SPtr<MeshComponent>& meshComp)
	{
		UINT vertexCount = meshComp->GetMesh()->GetVertexCount();
		ImGui::Text(("vertextCount : " + std::to_string(vertexCount)).c_str());
	}
}
