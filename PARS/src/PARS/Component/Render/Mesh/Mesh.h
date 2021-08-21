#pragma once

#include "PARS/Component/Render/Mesh/Vertex.h"

namespace PARS
{
	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh() = default;

		virtual void Shutdown();
		virtual void Draw(ID3D12GraphicsCommandList* commandList);

		void SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology);
		virtual void SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {}		
		virtual void ReleaseUploadBuffers();

		int GetVertexCount() const { return m_RealVertexCount; }

		const std::string& GetFileName() const { return m_FileName; }

	public:
		virtual bool LoadObj(const std::string& path);

	protected:
		std::string m_FileName;

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

	public:
		virtual bool LoadObj(const std::string& path) override;
		bool LoadMtl(const std::string& path, std::unordered_map<std::string, Vec4>& diffuse);

	private:
		std::vector<DiffuseVertex> m_DiffuseVertices;
		std::vector<UINT> m_Indices;
	};
}


