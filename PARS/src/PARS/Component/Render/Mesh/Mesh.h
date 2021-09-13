#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Component/Render/Mesh/Vertex.h"

namespace PARS
{
	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh() = default;

		virtual void Shutdown();
		virtual void BeginDraw(ID3D12GraphicsCommandList* commandList);
		virtual void Draw(ID3D12GraphicsCommandList* commandList);
		virtual void Draw(ID3D12GraphicsCommandList* commandList, UINT instanceCount, UINT subMeshCount) {}

		void SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);
		virtual void SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}	
		virtual void ReleaseUploadBuffers();

		int GetVertexCount() const { return m_RealVertexCount; }
		void SetRealVertexCount(int count) { m_RealVertexCount = count; }

		const std::string& GetObjectName() const { return m_ObjectName; }
		void SetObjectName(const std::string& name) { m_ObjectName = name; }

	protected:
		std::string m_ObjectName;

	protected:
		ID3D12Resource* m_VertexBuffer = nullptr;
		ID3D12Resource* m_VertexUploadBuffer = nullptr;

		D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;

		UINT m_Slot = 0;
		UINT m_VertexCount = 0;
		UINT m_Stride = 0;
		UINT m_Offset = 0;

		ID3D12Resource* m_IndexBuffer = nullptr;
		ID3D12Resource* m_IndexUploadBuffer = nullptr;

		D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;
		
		UINT m_IndexCount = 0;

		D3D12_PRIMITIVE_TOPOLOGY m_PrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		bool b_DrawIndex = false;
		int m_RealVertexCount = 0;
	};

	class DiffuseMesh : public Mesh
	{
	public:
		DiffuseMesh();
		virtual ~DiffuseMesh() = default;

		void SetVertex(const std::vector<DiffuseVertex>& vertices);
		void SetVertex(const std::vector<DiffuseVertex>& vertices, const std::vector<UINT>& indices);
		virtual void SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;
		
		const std::vector<DiffuseVertex>& GetDiffuseVertices() const { return m_DiffuseVertices; }
		std::vector<DiffuseVertex>& GetDiffseVertices() { return m_DiffuseVertices; }

	private:
		std::vector<DiffuseVertex> m_DiffuseVertices;
		std::vector<UINT> m_Indices;
	};

	struct DrawInfo
	{
		UINT vertexCount;
		UINT startLocation;
	};

	class Material;

	class MaterialMesh : public Mesh
	{
	public:
		MaterialMesh();
		virtual ~MaterialMesh() = default;

		virtual void Shutdown() override;
		virtual void Draw(ID3D12GraphicsCommandList* commandList, UINT instanceCount, UINT subMeshCount) override;

		void SetVertex(const std::vector<MaterialVertex>& vertices);
		void SetVertex(const std::vector<MaterialVertex>& vertices, const std::vector<UINT>& indices);
		virtual void SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;

	public:
		const std::vector<MaterialVertex>& GetMaterialVertices() const { return m_MaterialVertices; }
		std::vector<MaterialVertex>& GetMaterialVertices() { return m_MaterialVertices; }

		void SetMaterial(const SPtr<Material>& material, int index) { m_DefaultMaterials[index] = material; }
		const std::vector<SPtr<Material>>& GetMaterials() const  { return m_DefaultMaterials; }
		void AddMaterial(const SPtr<Material>& material) { m_DefaultMaterials.push_back(material); }

		void AddDrawInfo(DrawInfo&& info) { m_DrawInfos.emplace_back(std::move(info)); }

	private:
		std::vector<MaterialVertex> m_MaterialVertices;
		std::vector<UINT> m_Indices;
		std::vector<SPtr<Material>> m_DefaultMaterials;
		std::vector<DrawInfo> m_DrawInfos;
	};

	namespace OBJ
	{
		std::vector<SPtr<MaterialMesh>> LoadObj(const std::string& path, const std::string& parentPath);
	}
}
