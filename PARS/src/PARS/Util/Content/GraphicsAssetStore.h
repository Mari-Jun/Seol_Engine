#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class GraphicsAssetStore
	{
	private:
		static GraphicsAssetStore* s_Instance;

	public:
		GraphicsAssetStore();
		~GraphicsAssetStore() = default;

		bool Initialize();
		void Shutdown(); 

	private:
		void ConvertToPARSFile(const std::string& path);

	public:
		inline static GraphicsAssetStore* GetAssetStore() { return s_Instance; }
		const std::map<std::string, SPtr<class Mesh>>& GetMeshes() const { return m_MeshCache; }
		const std::map<std::string, SPtr<class Material>>& GetMaterials() const { return m_MaterialCache; }

		const SPtr<class Mesh>& GetMesh(const std::string& path) const;
		void LoadMesh(const std::string& path, const std::string& parentPath, const std::string& extension);
		const SPtr<class Material>& GetMaterial(const std::string& path) const;
		void LoadMaterial(const std::string& path, const std::string& parentPath, const std::string& extension);
		void SaveMaterial(const std::string& name, const SPtr<class Material>& material);		

	private:
		std::map<std::string, SPtr<class Mesh>> m_MeshCache;
		std::map<std::string, SPtr<class Material>> m_MaterialCache;
	};
}


