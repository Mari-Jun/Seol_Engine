#include "stdafx.h"
#include "PARS/Component/Render/Mesh/Mesh.h"
#include "PARS/Component/Render/Material/Material.h"
#include "PARS/Util/DirectX12/d3dUtil.h"
#include "PARS/Util/Content/AssetStore.h"

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

	void Mesh::BeginDraw(ID3D12GraphicsCommandList* commandList)
	{
		commandList->IASetPrimitiveTopology(m_PrimitiveTopology);
		commandList->IASetVertexBuffers(m_Slot, 1, &m_VertexBufferView);
		if (b_DrawIndex)
		{
			commandList->IASetIndexBuffer(&m_IndexBufferView);
		}
	}

	void Mesh::Draw(ID3D12GraphicsCommandList* commandList)
	{
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

	MaterialMesh::MaterialMesh()
	{
	}

	void MaterialMesh::Shutdown()
	{
		Mesh::Shutdown();
	}

	void MaterialMesh::Draw(ID3D12GraphicsCommandList* commandList, UINT instanceCount, UINT subMeshCount)
	{
		const auto& [count, location] = m_DrawInfos[subMeshCount];
		if (b_DrawIndex)
		{
			commandList->DrawIndexedInstanced(count, instanceCount, location, 0, 0);
		}
		else
		{
			commandList->DrawInstanced(count, instanceCount, location, 0);
		}
	}

	void MaterialMesh::SetVertex(const std::vector<MaterialVertex>& vertices)
	{
		m_MaterialVertices = vertices;

		m_VertexCount = static_cast<UINT>(vertices.size());
		m_Stride = sizeof(MaterialVertex);
	}

	void MaterialMesh::SetVertex(const std::vector<MaterialVertex>& vertices, const std::vector<UINT>& indices)
	{
		SetVertex(vertices);

		m_Indices = indices;
		m_IndexCount = static_cast<UINT>(indices.size());

		b_DrawIndex = true;
		m_RealVertexCount = m_VertexCount;
	}

	void MaterialMesh::SetBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)
	{
		if (m_VertexBuffer == nullptr)
		{
			m_VertexBuffer = D3DUtil::CreateBufferResource(device, commandList, m_MaterialVertices.data(), m_Stride * m_VertexCount,
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

	namespace OBJ
	{
		std::vector<SPtr<MaterialMesh>> LoadObj(const std::string& path, const std::string& parentPath)
		{
			std::vector<SPtr<MaterialMesh>> meshes;

			std::ifstream objFile(path);
			std::string stem = FILEHELP::GetStemFromPath(path);

			if (!objFile.is_open())
			{
				PARS_ERROR("Obj file could not be found : {0}", path);
			}
			else
			{
				std::vector<Vec3> positions;
				std::vector<Vec3> normals;
				std::vector<Vec2> texCoords;

				std::vector<UINT> posIndices;
				std::vector<UINT> normalIndices;
				std::vector<UINT> texIndices;
				std::vector<UINT> locations;

				std::stringstream ss;
				std::string line;
				std::string prefix;
				std::string mtlName;
				std::string objectName;

				Vec3 tempVec3;
				UINT tempUInt = 0;
				size_t vertexCount = 0;

				SPtr<MaterialMesh> mesh = nullptr;

				auto AddMesh([&]() {
					if (mesh != nullptr)
					{
						std::vector<MaterialVertex> materialVertices;
						materialVertices.resize(posIndices.size(), MaterialVertex());

						for (auto i = 0; i < posIndices.size(); ++i)
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

							materialVertices[index].SetPosition(positions[posIndices[i]]);
							materialVertices[index].SetNormal(normals[normalIndices[i]]);
							materialVertices[index].SetTexCoord(texCoords[texIndices[i]]);
						}


						for (int i = 0; i < locations.size() - 1; ++i)
							mesh->AddDrawInfo({ locations[i + 1] - locations[i], locations[i] });
						mesh->AddDrawInfo({ static_cast<UINT>(materialVertices.size()) - *(locations.end() - 1), *(locations.end() - 1) });

						mesh->SetRealVertexCount(positions.size() - vertexCount);
						vertexCount = positions.size();
						mesh->SetVertex(materialVertices);
						meshes.emplace_back(std::move(mesh));

						mesh = nullptr;
						posIndices.clear();
						normalIndices.clear();
						texIndices.clear();
						locations.clear();
					}
					});

				while (std::getline(objFile, line))
				{
					ss.clear();
					ss.str(line);
					ss >> prefix;

					if (prefix == "#")
					{
						ss >> prefix;
						if (prefix == "object")
						{
							AddMesh();
							mesh = CreateSPtr<MaterialMesh>();
							ss >> objectName;
							mesh->SetName(stem + "_" + objectName);
						}
					}
					else if (prefix == "v")
					{
						ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
						tempVec3.z *= -1.0f;
						positions.emplace_back(tempVec3);
					}
					else if (prefix == "vn")
					{
						ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
						tempVec3.z *= -1.0f;
						normals.emplace_back(tempVec3);
					}
					else if (prefix == "vt")
					{
						ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
						tempVec3.y = 1.0f - tempVec3.y;
						texCoords.emplace_back(Vec2{ tempVec3.x, tempVec3.y });
					}
					else if (prefix == "usemtl")
					{
						ss >> mtlName;
						const auto& material = AssetStore::GetAssetStore()->GetMaterial(parentPath + "\\" + mtlName);
						if (material == nullptr)
						{
							//obj, mtl관계에서는 mtl이 먼저 Load되는 것이 일반적이라서 발생할 가능성이 없다.
							//발생할 경우를 대비해서 Engine Content에서 기본 Material을 가져오는 것으로 할 것인데 아직은 작업 X
							PARS_CRITICAL("material load error!!!" + mesh->GetName());
						}
						mesh->AddMaterial(material);
						locations.push_back(static_cast<UINT>(posIndices.size()));
					}
					else if (prefix == "f")
					{
						int count = 0;

						while (ss >> tempUInt)
						{
							if (count == 0)
							{
								posIndices.emplace_back(tempUInt - 1);
							}
							else if (count == 1)
							{
								texIndices.emplace_back(tempUInt - 1);
							}
							else if (count == 2)
							{
								normalIndices.emplace_back(tempUInt - 1);
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
				}
				AddMesh();		
			}

			if (meshes.size() == 1)
			{
				meshes[0]->SetName(stem);
			}

			return meshes;
		}
	}
}
