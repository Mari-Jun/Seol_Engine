#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Util/Content/ContentHelper.h"

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
		const std::unordered_map<std::string, SPtr<Mesh>>& GetMeshes() const { return m_MeshCache; }
		const std::unordered_map<std::string, SPtr<Material>>& GetMaterials() const { return m_MaterialCache; }
		const std::unordered_map<std::string, SPtr<Texture>>& GetTextures() const { return m_TextureCache; }

		const SPtr<Mesh>& GetMesh(const std::string& path) const;
		void LoadMesh(std::set<ContentInfo>& contents, LoadContent& loadContents, const std::string& path);
		const SPtr<Material>& GetMaterial(const std::string& path) const;
		void LoadMaterial(std::set<ContentInfo>& contents, LoadContent& loadContents, const std::string& path);
		const SPtr<Texture>& GetTexture(const std::string& path) const;
		void LoadTexture(std::set<ContentInfo>& contents, LoadContent& loadContents, const std::string& path);

	private:
		std::unordered_map<std::string, SPtr<Mesh>> m_MeshCache;
		std::unordered_map<std::string, SPtr<Material>> m_MaterialCache;
		std::unordered_map<std::string, SPtr<Texture>> m_TextureCache;
	};
}


