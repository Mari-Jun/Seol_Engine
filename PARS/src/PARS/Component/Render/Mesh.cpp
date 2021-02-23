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
		if (m_IndexBuffer != nullptr) m_IndexBuffer->Release();
		if (m_IndexUploadBuffer != nullptr) m_IndexUploadBuffer->Release();
	}

	void Mesh::Draw(ID3D12GraphicsCommandList* commandList)
	{
		commandList->IASetPrimitiveTopology(m_PrimitiveTopology);
		commandList->IASetVertexBuffers(m_Slot, 1, &m_VertexBufferView);

		if (b_DrawIndex)
		{
			commandList->IASetIndexBuffer(&m_IndexBufferView);
			commandList->DrawIndexedInstanced(m_IndexCount, 1, 0, 0, 0);
		}
		else
		{
			commandList->DrawInstanced(m_VertexCount, 1, m_Offset, 0);
		}
		
	}

	void Mesh::SetPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
	{
		m_PrimitiveTopology = topology;
	}

	void Mesh::ReleaseUploadBuffers()
	{
		if (m_VertexUploadBuffer != nullptr)
		{
			m_VertexUploadBuffer->Release();
			m_VertexUploadBuffer = nullptr;
		}

		if (m_IndexUploadBuffer != nullptr)
		{
			m_IndexUploadBuffer->Release();
			m_IndexUploadBuffer = nullptr;
		}
	}

	DiffuseMesh::DiffuseMesh()
	{
	}

	void DiffuseMesh::SetVertex(const std::vector<DiffuseVertex>& vertices)
	{
		m_DiffuseVertices = vertices;

		m_VertexCount = static_cast<UINT>(vertices.size());
		m_Stride = sizeof(DiffuseVertex);
	}

	void DiffuseMesh::SetVertex(const std::vector<DiffuseVertex>& vertices, const std::vector<UINT>& indices)
	{
		SetVertex(vertices);

		m_Indices = indices;
		m_IndexCount = static_cast<UINT>(indices.size());

		b_DrawIndex = true;
	}

	void DiffuseMesh::SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		m_VertexBuffer = D3DUtil::CreateBufferResource(device, commandList, m_DiffuseVertices.data(), m_Stride * m_VertexCount,
			D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_VertexUploadBuffer);

		m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();
		m_VertexBufferView.StrideInBytes = m_Stride;
		m_VertexBufferView.SizeInBytes = m_VertexCount * m_Stride;

		if (b_DrawIndex)
		{
			m_IndexBuffer = D3DUtil::CreateBufferResource(device, commandList, m_Indices.data(), sizeof(UINT) * m_IndexCount,
				D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_IndexUploadBuffer);

			m_IndexBufferView.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
			m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
			m_IndexBufferView.SizeInBytes = sizeof(UINT) * m_IndexCount;
		}
	}
}
