#pragma once
#include "PARS/Math/Math.h"
#include "PARS/Util/Content/Asset.h"

namespace PARS
{
	class Texture;
	
	class Material : public Asset
	{
	public:
		Material() = default;
		virtual ~Material() = default;

	public:
		//Please Call these functions in AssetStore/ContentLayer/DetailFunctions..
		virtual void OpenEditLayer() override;

	private:
		int m_MatCBIndex = -1;
		int m_DiffuseMapIndex = -1;

		bool m_IsChangedMaterial = true;

		Vec4 m_DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		Vec3 m_FresnelR0 = { 0.01f, 0.01f, 0.0f };
		float m_Roughness = 1.0f;

		//Texture�� ���� ��ɵ��� ���� �����ִµ� ���� �� ���� Diffuse�� ����
		SPtr<Texture> m_DiffuseTexture;

	public:
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

		void SetDiffuseTexture(const SPtr<Texture> texture) { m_DiffuseTexture = texture; }
		const SPtr<Texture>& GetDiffuseTexture() const { return m_DiffuseTexture; }
	};

	namespace MTL
	{
		std::vector<SPtr<Material>> LoadMtl(const std::string& path);
	}

	struct CBMaterial
	{
		Vec4 diffuseAlbedo;
		Vec3 fresnelR0;
		float roughness;

		int diffuseMapIndex;
		UINT padding0;
		UINT padding1;
		UINT padding2;
	};
}



