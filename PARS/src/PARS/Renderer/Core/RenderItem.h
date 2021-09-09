#pragma once
#include "PARS/Core/Core.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	class Mesh;

	struct CBCurMatIndex
	{
		UINT index = 0;
	};

	struct RenderInstanceData
	{
		Mat4 worldMatrix;
		Mat4 worldInverseTranspose;
		std::array<UINT, 32> materialIndice;
	};

	struct RenderInstance
	{
		WPtr<class MeshComponent> meshComp;
		RenderInstanceData instanceData;
	};

	class RenderItem
	{
	public:
		RenderItem(const SPtr<Mesh>& mesh);
		virtual ~RenderItem() = default;

		void Shutdown();

		void Update(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		void UpdateShaderVariables();
		void Draw(ID3D12GraphicsCommandList* commandList);

	public:
		void AddMeshCompDrwanWithMesh(const SPtr<class MeshComponent>& meshComp);
		bool RemoveInstanceData(const SPtr<class MeshComponent>& meshComp);
		void ChangeMaterialForInstanceData(const SPtr<class MeshComponent>& meshComp, UINT index);

	private:
		SPtr<Mesh> m_Mesh = nullptr;
		std::vector<RenderInstance> m_Instances;

		ID3D12Resource* m_InstanceData = nullptr;
		BYTE* m_MappedInstanceData = nullptr;

		bool m_IsNeedMeshBufferUpdate = true;
		bool m_IsAddNewInstance = false;

	public:
		const std::string& GetMeshName() const;
		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }

	};

}



