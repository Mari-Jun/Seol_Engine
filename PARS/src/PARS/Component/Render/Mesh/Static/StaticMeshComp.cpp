#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshDF.h"

namespace PARS
{
	StaticMeshComponent::StaticMeshComponent()
		: MeshComponent("Static Mesh Component", RenderType::StaticMesh)
	{
	}

	void StaticMeshComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<StaticMeshCompDetailFunction>();
	}

	void StaticMeshComponent::UpdateShaderVariables(std::map<std::string, BYTE*> variables)
	{
		RenderComponent::UpdateShaderVariables(variables);

		m_Mesh->UpdateShaderVariables(variables);
	}

	bool StaticMeshComponent::SetMesh(std::string&& path)
	{
		//Mesh ��ü ���� Ȯ��
		if (m_Mesh != nullptr)
		{
			m_Mesh = nullptr;
			SetRenderState(RenderState::Changed);
		}

		//�̹� Load������ �ִ��� Cache�����Ϳ��� ã�´�. 
		m_Mesh = GraphicsAssetStore::GetAssetStore()->GetMesh(path);

		return (m_Mesh != nullptr);
	}
}
