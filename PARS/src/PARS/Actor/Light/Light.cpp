#include "stdafx.h"
#include "PARS/Actor/Light/Light.h"

namespace PARS
{
	Light::Light()
	{
	}

	DirectionalLight::DirectionalLight()
	{
		m_LightComponent = CreateSPtr<DirectionalLightComponent>(Vec3{ 1.0f, 1.0f, 1.0f });
	}

	DirectionalLight::DirectionalLight(const Vec3& color)
	{
		m_LightComponent = CreateSPtr<DirectionalLightComponent>(color);
	}

	void DirectionalLight::Initialize()
	{
		AddComponent(m_LightComponent);
	}

	void DirectionalLight::Shutdown()
	{
	}


}