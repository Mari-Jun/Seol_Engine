#include "stdafx.h"
#include "PARS/Component/Light/Light.h"

namespace PARS
{
	Light::Light()
		: m_LightColor({ 1.0f, 1.0f, 1.0f })
		, m_FalloffStart(0.0f)
		, m_Direction({ 0.0f, 0.0f, 1.0f })
		, m_FalloffEnd(0.0f)
		, m_Position({ 0.0f, 0.0f, 0.0f })
		, m_SpotPower(0.0f)
	{
	}

	Light::Light(const Vec3& color, const Vec3& direction)
		: m_LightColor(color)
		, m_FalloffStart(0.0f)
		, m_Direction(direction)
		, m_FalloffEnd(0.0f)
		, m_Position({ 0.0f, 0.0f, 0.0f })
		, m_SpotPower(0.0f)
	{
	}

	Light::Light(const Vec3& color, float falloffStart, float falloffEnd, const Vec3& position)
		: m_LightColor(color)
		, m_FalloffStart(falloffStart)
		, m_Direction({ 0.0f, 0.0f, 1.0f })
		, m_FalloffEnd(falloffEnd)
		, m_Position(position)
		, m_SpotPower(0.0f)
	{
	}

	Light::Light(const Vec3& color, float falloffStart, const Vec3& direction, float falloffEnd, const Vec3& position, float spotPower)
		: m_LightColor(color)
		, m_FalloffStart(falloffStart)
		, m_Direction(direction)
		, m_FalloffEnd(falloffEnd)
		, m_Position(position)
		, m_SpotPower(spotPower)
	{
	}
}