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

	void StaticMeshComponent::UpdateShaderVariables(std::map<std::string, BYTE*> variables)
	{
		MeshComponent::UpdateShaderVariables(variables);
	}

	bool StaticMeshComponent::SetMesh(std::string&& path)
	{
		//Mesh ��ü ���� Ȯ��
		if (m_Mesh != nullptr)
		{
			RemoveFromRenderFactory();
			m_Mesh = nullptr;
		}

		//�̹� Load������ �ִ��� Cache�����Ϳ��� ã�´�. 
		const auto& mesh = std::reinterpret_pointer_cast<MaterialMesh>(AssetStore::GetAssetStore()->GetMesh(path));
		if (mesh != nullptr)
		{
			m_Mesh = mesh;
			m_Materials = mesh->GetMaterials();
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
			m_Materials = std::reinterpret_pointer_cast<MaterialMesh>(m_Mesh)->GetMaterials();
			AddToRenderFactory();
		}
	}
}
