#pragma once
#include "PARS/Layer/EngineLayer/EditLayer/Core/EditLayer.h"

namespace PARS
{
	class Material;

	class MaterialEditLayer : public EditLayer
	{
	public:
		MaterialEditLayer(const std::string& name, const WPtr<Material> material);
		virtual ~MaterialEditLayer() = default;

		virtual void Initialize() override;
		virtual void UpdateEditLayer() override;

	private:


	private:
		WPtr<Material> m_Material;
		bool m_IsFirstOpen = true;
	};
}


