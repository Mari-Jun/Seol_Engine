#pragma once

#include "PARS/Component/Render/Vertex.h"

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
	};

	class DiffuseMesh : public Mesh
	{
	public:
		DiffuseMesh();
		virtual ~DiffuseMesh() = default;

		void SetVertex(const std::vector<DiffuseVertex>& vertices);
		void SetVertex(const std::vector<DiffuseVertex>& vertices, const std::vector<UINT>& indices);
		virtual void SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) override;

	private:
		std::vector<DiffuseVertex> m_DiffuseVertices;
		std::vector<UINT> m_Indices;
	};
}


