#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshDF.h"
#include "PARS/Component/Render/Material/Material.h"

namespace PARS
{
	StaticMeshComponent::StaticMeshComponent()
		: MeshComponent("Static Mesh Component", MeshType::Static)
	{
	}

	void StaticMeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<StaticMeshCompDetailFunction>();
	}

	bool StaticMeshComponent::SetMesh(std::string&& path)
	{
		//Mesh 교체 여부 확인
		if (m_Mesh != nullptr)
		{
			RemoveFromRenderFactory();
			m_Mesh = nullptr;
		}

		//이미 Load된적이 있는지 Cache데이터에서 찾는다. 
		const auto& mesh = std::reinterpret_pointer_cast<MaterialMesh>(AssetStore::GetAssetStore()->GetMesh(path));
		if (mesh != nullptr)
		{
			m_Mesh = mesh;
			ResetMaterials();
			for (const auto& material : mesh->GetMaterials())
			{
				AddMaterial(material);
			}
			AddToRenderFactory();
		}

		return (m_Mesh != nullptr);
	}

	void StaticMeshComponent::SetMesh(const SPtr<Mesh>& mesh)
	{
		if (m_Mesh != nullptr)
		{
			RemoveFromRenderFactory();
			m_Mesh = nullptr;
		}

		if (mesh != nullptr)
		{
			m_Mesh = mesh;
			ResetMaterials();
			for (const auto& material : std::reinterpret_pointer_cast<MaterialMesh>(m_Mesh)->GetMaterials())
			{
				AddMaterial(material);
			}
			AddToRenderFactory();
		}
	}
}
