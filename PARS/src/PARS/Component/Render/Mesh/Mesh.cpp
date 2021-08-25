#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Util/DirectX12/d3dUtil.h"
#include "PARS/Util/Helper/ContentHelper.h"

namespace PARS
{
	Mesh::Mesh()
	{
	}

	void Mesh::Shutdown()
	{
		if (m_VertexBuffer != nullptr) m_VertexBuffer->Release();
		m_VertexBuffer = nullptr;
		if (m_VertexUploadBuffer != nullptr) m_VertexUploadBuffer->Release();
		m_VertexUploadBuffer = nullptr;
		if (m_IndexBuffer != nullptr) m_IndexBuffer->Release();
		m_IndexBuffer = nullptr;
		if (m_IndexUploadBuffer != nullptr) m_IndexUploadBuffer->Release();
		m_IndexUploadBuffer = nullptr;
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

	bool Mesh::LoadObj(const std::string& path)
	{
		return true;
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
		m_RealVertexCount = m_VertexCount;
	}

	void DiffuseMesh::SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		if (m_VertexBuffer == nullptr)
		{
			m_VertexBuffer = D3DUtil::CreateBufferResource(device, commandList, m_DiffuseVertices.data(), m_Stride * m_VertexCount,
				D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_VertexUploadBuffer);

			m_VertexBufferView.BufferLocation = m_VertexBuffer->GetGPUVirtualAddress();
			m_VertexBufferView.StrideInBytes = m_Stride;
			m_VertexBufferView.SizeInBytes = m_VertexCount * m_Stride;
		}

		if (b_DrawIndex)
		{
			if (m_IndexBuffer == nullptr)
			{
				m_IndexBuffer = D3DUtil::CreateBufferResource(device, commandList, m_Indices.data(), sizeof(UINT) * m_IndexCount,
					D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_IndexUploadBuffer);

				m_IndexBufferView.BufferLocation = m_IndexBuffer->GetGPUVirtualAddress();
				m_IndexBufferView.Format = DXGI_FORMAT_R32_UINT;
				m_IndexBufferView.SizeInBytes = sizeof(UINT) * m_IndexCount;
			}
		}
	}

	bool DiffuseMesh::LoadObj(const std::string& path)
	{
		m_FileName = ContentHelper::GetFileNameFromPath(path);
		std::ifstream objFile(path);

		if (!objFile.is_open())
		{
			PARS_ERROR("Obj file could not be found : {0}", m_FileName);
			return false;
		}

		std::unordered_map<std::string, Vec4> diffuseColor;
		if (!LoadMtl(path.substr(0, path.size() - 4), diffuseColor))
		{
			return false;
		}

		std::vector<Vec3> position;
		std::vector<Vec3> normal;
		
		std::vector<UINT> posIndex;
		std::vector<UINT> normalIndex;
		std::vector<std::string> mtlIndex;

		std::stringstream ss;
		std::string line;
		std::string prefix;
		std::string mtlName;

		Vec3 tempVec3;
		UINT tempUInt = 0;

		while (std::getline(objFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;


			if (prefix == "v")
			{
				ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				tempVec3.z *= -1.0f;
				position.emplace_back(tempVec3);
			}
			else if (prefix == "vn")
			{
				ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				tempVec3.z *= -1.0f;
				normal.emplace_back(tempVec3);
			}
			else if (prefix == "usemtl")
			{
				ss >> mtlName;
			}
			else if (prefix == "f")
			{
				int count = 0;
				
				while (ss >> tempUInt)
				{
					if (count == 0)
					{
						posIndex.emplace_back(tempUInt - 1);
						mtlIndex.emplace_back(mtlName);
					}
					else if (count == 1)
					{
						//texcoord °ª
					}
					else if (count == 2)
					{
						normalIndex.emplace_back(tempUInt - 1);
					}

					if (ss.peek() == '/')
					{
						++count;
						ss.ignore();
					}
					else if (ss.peek() == ' ')
					{
						ss.ignore(1, ' ');
						count = 0;
					}
				}
			}
			else if (prefix == "#" && m_RealVertexCount == 0)
			{
				int count;
				std::string name;
				ss >> count >> name;
				if (name == "vertices")
					m_RealVertexCount = count;
			}
		}

		m_DiffuseVertices.resize(posIndex.size(), DiffuseVertex());

		for (auto i = 0; i < posIndex.size(); ++i)
		{
			auto index = i;
			if (index % 3 == 0)
			{
				index += 2;
			}
			else if (index % 3 == 2)
			{
				index -= 2;
			}

			m_DiffuseVertices[index].SetPosition(position[posIndex[i]]);
			m_DiffuseVertices[index].SetNormal(normal[normalIndex[i]]);
			m_DiffuseVertices[index].SetDiffuseColor(diffuseColor[mtlIndex[i]]);
		}

		m_VertexCount = static_cast<UINT>(m_DiffuseVertices.size());
		m_Stride = sizeof(DiffuseVertex);

		return true;
	}


	bool DiffuseMesh::LoadMtl(const std::string& path, std::unordered_map<std::string, Vec4>& diffuse)
	{
		std::string mtlName = CONTENT_DIR + path + ".mtl";
		std::ifstream mtlFile(mtlName);

		if (!mtlFile.is_open())
		{
			PARS_ERROR("Obj file could not be found : {0}", mtlName);
			return false;
		}

		std::stringstream ss;
		std::string line;
		std::string prefix;
		std::string name;

		Vec4 tempVec4;

		while (std::getline(mtlFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;

			if (prefix == "newmtl")
			{
				ss >> name;
			}
			else if (prefix == "Kd")
			{
				ss >> tempVec4.x >> tempVec4.y >> tempVec4.z;
				tempVec4.w = 1.0f;
				diffuse.emplace(name, std::move(tempVec4));
			}
		}

		return true;
	}
}
