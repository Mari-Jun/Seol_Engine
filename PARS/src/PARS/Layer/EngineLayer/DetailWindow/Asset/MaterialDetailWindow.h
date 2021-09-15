#pragma once
#include "PARS/Layer/EngineLayer/DetailWindow/Core/DetailWindow.h"

namespace PARS
{
	class Material;

	class MaterialDW : public DetailWindow
	{
	public:
		MaterialDW(const std::string& windowName);
		virtual ~MaterialDW() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void ProcessInput() override;
		virtual void Update() override;

	private:
		WPtr<Material> m_Material;
	};
}


