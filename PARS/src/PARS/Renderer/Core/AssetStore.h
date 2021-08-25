#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class AssetStore
	{
	private:
		static AssetStore* s_Instance;

	public:
		AssetStore(const SPtr<class DirectX12>& directX);
		~AssetStore() = default;

		bool Initialize();
		void Shutdown(); 

	public:
		inline static AssetStore* GetAssetStore() { return s_Instance; }

		const SPtr<class Mesh>& GetMesh(const std::string& fileName) const;
		void SaveMesh(const std::string& fileName, const SPtr<class Mesh>& mesh);

	private:
		SPtr<class DirectX12> m_DirectX12;
		std::unordered_map<std::string, SPtr<class Mesh>> m_MeshCache;
		std::unordered_map<std::string, SPtr<class Material>> m_MaterialCache;
	};
}


