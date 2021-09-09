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
		//Mesh 교체 여부 확인
		if (m_Mesh != nullptr)
		{
			RemoveFromRenderFactory();
			m_Mesh = nullptr;
			SetRenderState(RenderState::Changed);
		}

		//이미 Load된적이 있는지 Cache데이터에서 찾는다. 
		const auto& mesh = std::reinterpret_pointer_cast<MaterialMesh>(GraphicsAssetStore::GetAssetStore()->GetMesh(path));
		if (mesh != nullptr)
		{
			//공유는 하는데.. Material을 교체하게되면 그것은 AssetStore에 저장되어 있지 않은 새로운 Mesh다.\
			//하지만 저장은 하지 않고 RenderFactory에만 저장이 될 것이다.
			//Render Factory 추가할 때 정보 확인 즉 Mesh의 이름과, Material들의 이름이 모두 같으면 같은 물체라고 판단해야한다. <-이게 맞아?
			//그냥 Mesh는 Material이 다르던 말던 같아야 되는거 아닌가?
			m_Mesh = mesh;
			m_Materials = mesh->GetMaterials();
			AddToRenderFactory();
		}

		return (m_Mesh != nullptr);
	}
}
