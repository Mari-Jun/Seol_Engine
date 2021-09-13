#pragma once

#include "PARS/Actor/Actor.h"
#include "PARS/Component/Light/LightComponent.h"

namespace PARS
{
	class Light : public Actor
	{
	public:
		Light(const std::string& name = "Light") : Actor(name) {}
		/*Light(const Vec3& color, float falloffStart, float falloffEnd);
		Light(const Vec3& color, float falloffStart, float falloffEnd, float spotPower);*/

		const SPtr<LightComponent>& GetLightComponent() const { return m_LightComponent; }

	protected:
		SPtr<LightComponent> m_LightComponent;
	};
}


