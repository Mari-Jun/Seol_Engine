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
		virtual void UpdateShaderVariables(std::map<std::string, BYTE*> variables);
		virtual void UpdateMaterialShaderVariables(BYTE* variable, UINT instance, UINT offset);
		virtual void ReleaseUploadBuffers();

	protected:
		void AddToRenderFactory();
		void RemoveFromRenderFactory();

	public:
		MeshType GetMeshType() const { return m_MeshType; }
		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }
		void SetInstanceIndex(UINT index) { m_InstanceIndex = index;}
		UINT GetInstanceIndex() const { return m_InstanceIndex; }
		void SetMaterial(const SPtr<Material>& material, int index) { m_Materials[index] = material; }
		const std::vector<SPtr<Material>>& GetMaterials() const { return m_Materials; }
		void AddMaterial(const SPtr<Material>& material) { m_Materials.push_back(material); }

	protected:
		MeshType m_MeshType;
		SPtr<Mesh> m_Mesh = nullptr;
		UINT m_InstanceIndex = 0;
		std::vector<SPtr<Material>> m_Materials;
	};

}


