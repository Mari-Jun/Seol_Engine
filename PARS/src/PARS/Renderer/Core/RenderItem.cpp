#include "stdafx.h"
#include "PARS/Util/DirectX12/d3dUtil.h"
#include "PARS/Renderer/Core/RenderItem.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Component/Render/Material/Material.h"

namespace PARS
{
	RenderItem::RenderItem(const SPtr<Mesh>& mesh, UINT matCount)
		: m_Mesh(mesh)
		, m_MaterialCount(matCount)
	{
		
	}

	void RenderItem::Shutdown()
	{
		if (m_InstanceData != nullptr)
		{
			m_InstanceData->Unmap(0, nullptr);
			m_InstanceData->Release();
			m_InstanceData = nullptr;
		}

		if (m_MatInstanceData != nullptr)
		{
			m_MatInstanceData->Unmap(0, nullptr);
			m_MatInstanceData->Release();
			m_MatInstanceData = nullptr;
		}
	}

	void RenderItem::Update(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		//이 부분도 수정해야한다.
		if (m_IsNeedMeshBufferUpdate)
		{
			if (m_Mesh != nullptr)
			{
				m_Mesh->SetBuffer(device, commandList);
			}
			m_IsNeedMeshBufferUpdate = false;
		}

		if (m_AddInstanceCount > 0)
		{
			RenderReady(device, commandList);
			m_AddInstanceCount = 0;
		}
		
		UpdateShaderVariables();
	}

	void RenderItem::RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		const auto& instanceSize = m_Instances.size() * sizeof(RenderInstanceData);
		auto beforeSize = (m_Instances.size() - m_AddInstanceCount) * sizeof(RenderInstanceData);

		BYTE* instanceData = nullptr;
		
		if (beforeSize > 0)
		{
			instanceData = new BYTE[beforeSize];
			memcpy(instanceData, m_MappedInstanceData, beforeSize);
		}

		if (m_InstanceData != nullptr)
		{
			m_InstanceData->Unmap(0, nullptr);
			m_InstanceData->Release();
			m_InstanceData = nullptr;
		}

		m_InstanceData = D3DUtil::CreateBufferResource(device, commandList, nullptr, instanceSize,
			D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);


		if (FAILED(m_InstanceData->Map(0, nullptr, (void**)&m_MappedInstanceData)))
		{
			PARS_ERROR("InstanceData Mapping Error");
		}

		if (instanceData != nullptr)
		{
			memcpy(m_MappedInstanceData, instanceData, beforeSize);
			delete[] instanceData;
			instanceData = nullptr;
		}

		m_MatInstanceDataSize = m_Instances.size() * sizeof(MaterialInstanceData);
		beforeSize = (m_Instances.size() - m_AddInstanceCount) * sizeof(MaterialInstanceData);

		BYTE* matInstanceData = nullptr;

		if (beforeSize > 0)
		{
			matInstanceData = new BYTE[m_MaterialCount * beforeSize];
			memcpy(matInstanceData, m_MatInstanceMappedData, m_MaterialCount * beforeSize);
		}

		if (m_MatInstanceData != nullptr)
		{
			m_MatInstanceData->Unmap(0, nullptr);
			m_MatInstanceData->Release();
			m_MatInstanceData = nullptr;
		}

		m_MatInstanceData = D3DUtil::CreateBufferResource(device, commandList, nullptr, m_MaterialCount * m_MatInstanceDataSize,
			D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, nullptr);

		if (FAILED(m_MatInstanceData->Map(0, nullptr, (void**)&m_MatInstanceMappedData)))
		{
			PARS_ERROR("MatInstanceData Mapping Error");
		}

		
		if (matInstanceData != nullptr)
		{
			for (int i = 0; i < m_MaterialCount; ++i)
			{
				memcpy(m_MatInstanceMappedData + i * m_MatInstanceDataSize, matInstanceData + i * beforeSize, beforeSize);
			}
			delete[] matInstanceData;
		}
	}

	void RenderItem::UpdateShaderVariables()
	{
		int index = 0;
		for (const auto& instance : m_Instances)
		{
			const auto& meshComp = instance.meshComp.lock();
			const auto& owner = meshComp->GetOwner().lock();

			if (owner->IsChangedWorldMatrix())
			{
				Mat4 worldMatrix = owner->GetWorldMatrix();
				Mat4 worldInverseTranspose = Mat4::InverseTranspose(worldMatrix);
				worldMatrix.Transpose();
				worldInverseTranspose.Transpose();

				RenderInstanceData data;
				data.worldMatrix = worldMatrix;
				data.worldInverseTranspose = worldInverseTranspose;

				memcpy(&m_MappedInstanceData[index * sizeof(RenderInstanceData)], &data, sizeof(RenderInstanceData));

				owner->ResetChangedWorldMatrix();
			}

			const auto materials = meshComp->GetMaterials();

			int matIndex = 0;
			for (const auto& [material, needUpdate] : materials)
			{
				if (needUpdate)
				{
					MaterialInstanceData data;
					data.matIndex = material->GetMatCBIndex();
					memcpy(&m_MatInstanceMappedData[matIndex * m_MatInstanceDataSize + index * sizeof(MaterialInstanceData)],
						&data, sizeof(MaterialInstanceData));
					meshComp->SetMaterialNeedUpdateShader(matIndex, false);
					++matIndex;
				}
			}
			++index;
		}
	}

	void RenderItem::Draw(ID3D12GraphicsCommandList* commandList)
	{
		commandList->SetGraphicsRootShaderResourceView(0, m_InstanceData->GetGPUVirtualAddress());
		if (m_Mesh != nullptr)
		{
			m_Mesh->BeginDraw(commandList);
			for (UINT i = 0; i < m_MaterialCount; ++i)
			{
				commandList->SetGraphicsRootShaderResourceView(1, m_MatInstanceData->GetGPUVirtualAddress() + i * m_MatInstanceDataSize);
				m_Mesh->Draw(commandList, m_Instances.size(), i);
			}
		}
	}

	void RenderItem::AddMeshCompDrwanWithMesh(const SPtr<class MeshComponent>& meshComp)
	{
		const auto& owner = meshComp->GetOwner().lock();

		RenderInstance renderInstance;
		renderInstance.meshComp = meshComp;

		if(owner != nullptr)
			owner->SetIsChangedWorldMatrix(true);

		meshComp->SetInstanceIndex(m_Instances.size());
		m_Instances.emplace_back(std::move(renderInstance));
			
		++m_AddInstanceCount;
	}

	bool RenderItem::RemoveInstanceData(const SPtr<class MeshComponent>& meshComp)
	{
		UINT index = meshComp->GetInstanceIndex();

		std::swap(*(m_Instances.begin() + index), *(m_Instances.end() - 1));
		m_Instances[index].meshComp.lock()->SetInstanceIndex(index);
		m_Instances[index].meshComp.lock()->GetOwner().lock()->SetIsChangedWorldMatrix(true);

		m_Instances.pop_back();

		return m_Instances.empty();
	}

	const std::string& RenderItem::GetMeshName() const
	{
		return m_Mesh->GetName();
	}
}
