#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshDF.h"
#include "PARS/Component/Render/Material/Material.h"

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
		MeshComponent::UpdateShaderVariables(variables);

		if (variables.find("CBConvertMatIndex") != variables.cend())
		{
			CBConvertMatIndex mappedConvertIndex;

			int index = 0;
			for (const auto& material : m_Materials)
			{
				mappedConvertIndex.indice[index] = material->GetMatCBIndex();
				++index;
			}

			memcpy(variables["CBConvertMatIndex"], &mappedConvertIndex, sizeof(CBConvertMatIndex));
		}

		//m_Mesh->UpdateShaderVariables(variables);
	}

	bool StaticMeshComponent::SetMesh(std::string&& path)
	{
		//Mesh ��ü ���� Ȯ��
		if (m_Mesh != nullptr)
		{
			RemoveFromRenderFactory();
			m_Mesh = nullptr;
			SetRenderState(RenderState::Changed);
		}

		//�̹� Load������ �ִ��� Cache�����Ϳ��� ã�´�. 
		const auto& mesh = std::reinterpret_pointer_cast<MaterialMesh>(GraphicsAssetStore::GetAssetStore()->GetMesh(path));
		if (mesh != nullptr)
		{
			//������ �ϴµ�.. Material�� ��ü�ϰԵǸ� �װ��� AssetStore�� ����Ǿ� ���� ���� ���ο� Mesh��.\
			//������ ������ ���� �ʰ� RenderFactory���� ������ �� ���̴�.
			//Render Factory �߰��� �� ���� Ȯ�� �� Mesh�� �̸���, Material���� �̸��� ��� ������ ���� ��ü��� �Ǵ��ؾ��Ѵ�. <-�̰� �¾�?
			//�׳� Mesh�� Material�� �ٸ��� ���� ���ƾ� �Ǵ°� �ƴѰ�?
			m_Mesh = mesh;
			m_Materials = mesh->GetMaterials();
			AddToRenderFactory();
		}

		return (m_Mesh != nullptr);
	}
}
