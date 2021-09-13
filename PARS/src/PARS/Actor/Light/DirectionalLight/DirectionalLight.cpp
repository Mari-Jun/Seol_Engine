#include "stdafx.h"
#include "PARS/Actor/Light/DirectionalLight/DirectionalLight.h"	

namespace PARS
{
	DirectionalLight::DirectionalLight(const std::string& name)
		: Light(name)
	{
		m_LightComponent = CreateSPtr<DirectionalLightComponent>(Vec3{ 1.0f, 1.0f, 1.0f });
	}

	DirectionalLight::DirectionalLight(const Vec3& color, const std::string& name)
		: Light(name)
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