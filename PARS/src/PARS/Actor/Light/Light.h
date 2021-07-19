#pragma once

#include "PARS/Actor/Actor.h"
#include "PARS/Component/Light/LightComponent.h"

namespace PARS
{
	class Light : public Actor
	{
	public:
		Light();
		/*Light(const Vec3& color, float falloffStart, float falloffEnd);
		Light(const Vec3& color, float falloffStart, float falloffEnd, float spotPower);*/

	protected:
		SPtr<class LightComponent> m_LightComponent;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight();
		DirectionalLight(const Vec3& color);

		virtual void Initialize() override;
		virtual void Shutdown() override;
		//virtual void Update(float deltaTime) {}
	};
}


