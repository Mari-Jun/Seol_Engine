#pragma once
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Component/Render/RenderComponent.h"

namespace PARS
{
	class DirectX12;

	class MeshComponent : public RenderComponent
	{
	public:
		MeshComponent(const std::string& name, RenderType type);
		virtual ~MeshComponent() = default;

		virtual void Initialize() override;
		virtual void InitializeDetailFunction() override;
		virtual void Shutdown() override;
		virtual void Draw(ID3D12GraphicsCommandList* commandList) override;

		virtual void RenderReady(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;
		virtual void UpdateShaderVariables(std::map<std::string, BYTE*> variables) override;
		virtual void ReleaseUploadBuffers() override;

	protected:
		void AddToRenderFactory();
		void RemoveFromRenderFactory();

	public:
		enum class FileType
		{
			Obj
		};

		const SPtr<Mesh>& GetMesh() const { return m_Mesh; }
		void SetInstanceIndex(UINT index) { m_InstanceIndex = index;}
		UINT GetInstanceIndex() const { return m_InstanceIndex; }
		void SetMaterial(const SPtr<Material>& material, int index) { m_Materials[index] = material; }
		const std::vector<SPtr<Material>>& GetMaterials() const { return m_Materials; }
		std::array<UINT, 32> GetMaterialIndices() const;
		void AddMaterial(const SPtr<Material>& material) { m_Materials.push_back(material); }

	protected:
		SPtr<Mesh> m_Mesh = nullptr;
		UINT m_InstanceIndex = 0;
		std::vector<SPtr<Material>> m_Materials;
	};

}


