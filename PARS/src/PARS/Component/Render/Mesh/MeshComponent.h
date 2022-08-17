#pragma once
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Component/Component.h"

namespace PARS
{
	class DirectX12;

	enum class MeshType
	{
		Static,
		Handmade,
	};

	struct MaterialData
	{
		SPtr<Material> material;
		bool isNeedUpdateShader = true;
	};

	class MeshComponent : public Component
	{
	public:
		MeshComponent(const std::string& name, MeshType type);
		virtual ~MeshComponent() = default;

		virtual void Initialize() override;
		virtual void InitializeDetailFunction() override;
		virtual void Shutdown() override;
		virtual void Draw(ID3D12GraphicsCommandList* commandList);

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
		virtual void ReleaseUploadBuffers();

	protected:
		void AddToRenderFactory();
		void RemoveFromRenderFactory();

	public:
		MeshType GetMeshType() const { return m_MeshType; }
		virtual void SetMesh(const SPtr<Mesh>& mesh) { m_Mesh = mesh; }
		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }
		void SetInstanceIndex(UINT index) { m_InstanceIndex = index;}
		UINT GetInstanceIndex() const { return m_InstanceIndex; }
		void SetMaterial(const SPtr<Material>& material, int index) { m_Materials[index] = { material, true }; }
		void SetMaterialNeedUpdateShader(int index, bool value) { m_Materials[index].isNeedUpdateShader = false; }
		const std::vector<MaterialData>& GetMaterials() const { return m_Materials; }
		void AddMaterial(const SPtr<Material>& material) { m_Materials.push_back({ material, true }); }
		void ResetMaterials() { m_Materials.clear(); }

	protected:
		MeshType m_MeshType;
		SPtr<Mesh> m_Mesh = nullptr;
		UINT m_InstanceIndex = 0;
		std::vector<MaterialData> m_Materials;
	};

}


