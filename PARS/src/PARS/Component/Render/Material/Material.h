#pragma once
#include "PARS/Math/Math.h"
#include "PARS/Core/Core.h"

namespace PARS
{
	class Material
	{
	public:
		Material() = default;
		virtual ~Material() = default;
		
	private:
		std::string m_Name;

		int m_MatCBIndex = -1;
		int m_DiffuseSrvHeapIndex = -1;

		bool m_IsChangedMaterial = true;

		Vec4 m_DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		Vec3 m_FresnelR0 = { 0.01f, 0.01f, 0.0f };
		float m_Roughness = 0.25f;

	public:
		const std::string& GetName() const { return m_Name; }
		void SetName(const std::string& name) { m_Name = name; }
		int GetMatCBIndex() const { return m_MatCBIndex; }
		int& GetMatCBIndex() { return m_MatCBIndex; }
		void SetMatCBIndex(int index) { m_MatCBIndex = index; }
		bool IsChangedMaterial() const { return m_IsChangedMaterial; }
		
		const Vec4& GetDiffuseAlbedo() const { return m_DiffuseAlbedo; }
		void SetDiffuseAlbedo(const Vec4& diffuse) { m_DiffuseAlbedo = diffuse; } 
		const Vec3& GetFresnelR0() const { return m_FresnelR0; }
		void SetFresnelR0(const Vec3& fresnel) { m_FresnelR0 = fresnel; }
		float GetRoughness() const { return m_Roughness; }
		void SetRoughness(float roughness) { m_Roughness = roughness; }
	};

	namespace MTL
	{
		std::vector<SPtr<Material>> LoadMtl(const std::string& path);
	}

	struct CBMaterial
	{
		Vec4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		Vec3 FresnelR0 = { 0.01f, 0.01f, 0.0f };
		float Shininess = 0.25f;
	};

	struct CBMaterials
	{
		CBMaterial m_Materials[1024];
	};
}



