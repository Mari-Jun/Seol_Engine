#pragma once
#include "PARS/Core/Core.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	class Mesh;

	struct RenderInstanceData
	{
		Mat4 worldMatrix;
		Mat4 worldInverseTranspose;
	};

	struct MaterialInstanceData
	{
		UINT matIndex;
	};

	struct RenderInstance
	{
		WPtr<class MeshComponent> meshComp;
		RenderInstanceData instanceData;
	};

	class RenderItem
	{
	public:
		RenderItem(const SPtr<Mesh>& mesh, UINT matCount);
		virtual ~RenderItem() = default;

		void Shutdown();

		void Update(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		void UpdateShaderVariables();
		void Draw(ID3D12GraphicsCommandList* commandList);

	public:
		void AddMeshCompDrwanWithMesh(const SPtr<class MeshComponent>& meshComp);
		bool RemoveInstanceData(const SPtr<class MeshComponent>& meshComp);

	private:
		SPtr<Mesh> m_Mesh = nullptr;
		UINT m_MaterialCount = 0;
		std::vector<RenderInstance> m_Instances;

		ID3D12Resource* m_InstanceData = nullptr;
		BYTE* m_MappedInstanceData = nullptr;

		ID3D12Resource* m_MatInstanceData = nullptr;
		BYTE* m_MatInstanceMappedData = nullptr;
		UINT m_MatInstanceDataSize = 0;

		bool m_IsNeedMeshBufferUpdate = true;
		UINT m_AddInstanceCount = 0;
	
	public:
		const std::string& GetMeshName() const;
		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }

	};

}



