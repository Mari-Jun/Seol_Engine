#include "stdafx.h"
#include "PARS/Component/Render/Mesh.h"
#include "PARS/Util/DirectX12/d3dUtil.h"

namespace PARS
{
	Mesh::Mesh()
	{
	}

	void Mesh::Shutdown()
	{
		if (m_VertexBuffer != nullptr) m_VertexBuffer->Release();
		if (m_VertexUploadBuffer != nullptr) m_VertexUploadBuffer->Release();
	}

	void Mesh::Draw(ID3D12GraphicsCommandList* commandList)
	{
		commandList->IASetPrimitiveTopology(m_PrimitiveTopology);
		commandList->IASetVertexBuffers(m_Slot, 1, &m_VertexBufferView);
		commandList->DrawInstanced(m_VertexCount, 1, m_Offset, 0);
	}

	void Mesh::SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
	{
		m_PrimitiveTopology = topology;
	}

	DiffuseMesh::DiffuseMesh()
	{
	}

	void DiffuseMesh::SetVertex(const std::vector<DiffuseVertex>& vertex)
	{
		m_DiffuseVertex = vertex;

		m_VertexCount = vertex.size();
		m_Stride = sizeof(DiffuseVertex);
	}

	void DiffuseMesh::SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_VertexBuffer = D3DUtil::CreateBufferResource(device, commandList, m_DiffuseVertex.data(), m_Stride * m_VertexCount,
			D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_VertexUploadBuffer);

		m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();
		m_VertexBufferView.StrideInBytes = m_Stride;
		m_VertexBufferView.SizeInBytes = m_VertexCount * m_Stride;
	}
}
