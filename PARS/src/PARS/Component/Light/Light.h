#pragma once

#include "PARS/Math/Math.h"

namespace PARS
{
	class Light
	{
	public:
		Light();
		Light(const Vec3& color, const Vec3& direction);
		Light(const Vec3& color, float falloffStart, float falloffEnd, const Vec3& position);
		Light(const Vec3& color, float falloffStart, const Vec3& direction, float falloffEnd, const Vec3& position, float spotPower);

		const Vec3& GetLightColor() const { return m_LightColor; }
		void SetLightColor(const Vec3& color) { m_LightColor = color; }
		const Vec3& GetDirection() const { return m_Direction; }

	protected:
		Vec3 m_LightColor;
		float m_FalloffStart;
		Vec3 m_Direction;
		float m_FalloffEnd;
		Vec3 m_Position;
		float m_SpotPower;
	};
}


