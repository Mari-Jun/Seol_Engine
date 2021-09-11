#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class Mesh;
	class Material;
	class Texture;

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
		const std::map<std::string, SPtr<Mesh>>& GetMeshes() const { return m_MeshCache; }
		const std::map<std::string, SPtr<Material>>& GetMaterials() const { return m_MaterialCache; }
		const std::map<std::string, SPtr<Texture>>& GetTextures() const { return m_TextureCache; }

		const SPtr<Mesh>& GetMesh(const std::string& path) const;
		void LoadMesh(const std::string& path, const std::string& parentPath, const std::string& extension);
		const SPtr<Material>& GetMaterial(const std::string& path) const;
		void LoadMaterial(const std::string& path, const std::string& parentPath, const std::string& extension);
		void SaveMaterial(const std::string& name, const SPtr<Material>& material);		
		const SPtr<Texture>& GetTexture(const std::string& path) const;
		void LoadTexture(const std::string& path, const std::string& parentPath,
			const std::string& stem, const std::string& extension);

	private:
		std::map<std::string, SPtr<Mesh>> m_MeshCache;
		std::map<std::string, SPtr<Material>> m_MaterialCache;
		std::map<std::string, SPtr<Texture>> m_TextureCache;
	};
}


