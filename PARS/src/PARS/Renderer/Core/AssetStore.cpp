#include "stdafx.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Component/Render/RenderComponent.h"
#include "PARS/Renderer/Core/AssetStore.h"
#include "PARS/Component/Render/Mesh/Mesh.h"

#include "PARS/Renderer/Shader/ColorShader.h"

namespace PARS
{
	AssetStore::AssetStore(const SPtr<DirectX12>& directX)
		: m_DirectX12(directX)
	{
	}

	bool AssetStore::Initialize()
	{
		s_Instance = this;
		return true;
	}

	void AssetStore::Shutdown()
	{
		for (auto iter = m_MeshCache.begin(); iter != m_MeshCache.end(); ++iter)
		{
			iter->second->Shutdown();
		}
		m_MeshCache.clear();
	}

	const SPtr<Mesh>& AssetStore::GetMesh(const std::string& fileName) const
	{
		SPtr<Mesh> mesh = nullptr;

		auto iter = m_MeshCache.find(fileName);
		if (iter != m_MeshCache.end())
		{
			mesh = iter->second;
		}

		return mesh;
	}

	void AssetStore::SaveMesh(const std::string& fileName, const SPtr<class Mesh>& mesh)
	{
		m_MeshCache.emplace(fileName, mesh);
	}

	AssetStore* AssetStore::s_Instance = nullptr;
}
