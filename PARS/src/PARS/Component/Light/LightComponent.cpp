#include "stdafx.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Component/Light/LightComponent.h"


namespace PARS
{
	LightComponent::LightComponent(int updateOrder)
		: Component(updateOrder)
	{
	}

	void LightComponent::Initialize()
	{
		m_Light = CreateUPtr<Light>(Vec3{ 1.0f, 0.0f, 0.0f }, Vec3{ 0.0f, 0.0f, 1.0f });

		const auto& factory = RenderFactory::GetRenderFactory();
		factory->AddLightComponent(std::reinterpret_pointer_cast<LightComponent>(shared_from_this()));
	}

	void LightComponent::Shutdown()
	{
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->RemoveLightComponent(std::reinterpret_pointer_cast<LightComponent>(shared_from_this()));
	}
}
