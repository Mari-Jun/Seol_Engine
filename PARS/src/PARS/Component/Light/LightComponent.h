#pragma once

#include "PARS/Component/Render/RenderComponent.h"
#include "PARS/Component/Light/Light.h"

namespace PARS
{
	class LightComponent : public Component
	{
	public:
		LightComponent(int updateOrder = 100);
		virtual ~LightComponent() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;

		const Light* GetLight() const { return m_Light.get(); }

	public:
		enum class LightType
		{
			Directional, Point, Spot
		};

	private:
		UPtr<Light> m_Light;
	};
}



