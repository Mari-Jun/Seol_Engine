#include "stdafx.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Component/Light/LightComponent.h"

namespace PARS
{
	LightCB::LightCB()
		: m_LightColor({ 1.0f, 1.0f, 1.0f })
		, m_FalloffStart(0.0f)
		, m_Direction({ 0.0f, 0.0f, 1.0f })
		, m_FalloffEnd(0.0f)
		, m_Position({ 0.0f, 0.0f, 0.0f })
		, m_SpotPower(0.0f)
	{
	}

	LightCB::LightCB(const Vec3& color, const Vec3& direction)
		: m_LightColor(color)
		, m_FalloffStart(0.0f)
		, m_Direction(direction)
		, m_FalloffEnd(0.0f)
		, m_Position({ 0.0f, 0.0f, 0.0f })
		, m_SpotPower(0.0f)
	{
	}

	LightCB::LightCB(const Vec3& color, float falloffStart, float falloffEnd, const Vec3& position)
		: m_LightColor(color)
		, m_FalloffStart(falloffStart)
		, m_Direction({ 0.0f, 0.0f, 1.0f })
		, m_FalloffEnd(falloffEnd)
		, m_Position(position)
		, m_SpotPower(0.0f)
	{
	}

	LightCB::LightCB(const Vec3& color, float falloffStart, const Vec3& direction, float falloffEnd, const Vec3& position, float spotPower)
		: m_LightColor(color)
		, m_FalloffStart(falloffStart)
		, m_Direction(direction)
		, m_FalloffEnd(falloffEnd)
		, m_Position(position)
		, m_SpotPower(spotPower)
	{
	}

	LightComponent::LightComponent(LightType lightType, int updateOrder)
		: Component(updateOrder)
		, m_LightType(lightType)
	{
	}

	void LightComponent::Initialize()
	{
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->AddLightComponent(std::reinterpret_pointer_cast<LightComponent>(shared_from_this()));
	}

	void LightComponent::Shutdown()
	{
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->RemoveLightComponent(std::reinterpret_pointer_cast<LightComponent>(shared_from_this()));
	}

	LightCount::LightCount()
		: m_DLight(0)
		, m_PLight(0)
		, m_SLight(0)
	{
	}

	LightCount::LightCount(int dLight, int pLight, int sLight)
		: m_DLight(dLight)
		, m_PLight(pLight)
		, m_SLight(sLight)
	{
	}

	void LightCount::AddLightCount(LightComponent::LightType type)
	{
		switch (type)
		{
		case PARS::LightComponent::LightType::Directional:	++m_DLight;	break;
		case PARS::LightComponent::LightType::Point:		++m_PLight;	break;
		case PARS::LightComponent::LightType::Spot:			++m_SLight;	break;
		}
	}

	DirectionalLightComponent::DirectionalLightComponent(const Vec3& color)
		: LightComponent(LightType::Directional)
	{
		m_LightColor = color;
	}

	LightCB DirectionalLightComponent::GetLightCB() const
	{
		return LightCB{ m_LightColor, GetOwner().lock()->GetForward() };
	}
}
