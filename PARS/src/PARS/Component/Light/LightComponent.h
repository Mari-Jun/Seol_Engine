#pragma once

#include "PARS/Math/Math.h"

namespace PARS
{
	class LightCB
	{
	public:
		LightCB();
		LightCB(const Vec3& color, const Vec3& direction);
		LightCB(const Vec3& color, float falloffStart, float falloffEnd, const Vec3& position);
		LightCB(const Vec3& color, float falloffStart, const Vec3& direction, float falloffEnd, const Vec3& position, float spotPower);

		const Vec3& GetLightColor() const { return m_LightColor; }
		void SetLightColor(const Vec3& color) { m_LightColor = color; }
		const Vec3& GetDirection() const { return m_Direction; }

	private:
		Vec3 m_LightColor = { 1.0f, 1.0f, 1.0f };
		float m_FalloffStart = 0.0f;
		Vec3 m_Direction = { 0.0f, 0.0f, 1.0f };
		float m_FalloffEnd = 0.0f;
		Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_SpotPower = 0.0f;
	};

	class LightComponent : public Component
	{
	public:
		enum class LightType
		{
			Directional, Point, Spot
		};

	public:
		LightComponent(LightType lightType, const std::string& name = "LightComponent", int updateOrder = 100);
		virtual ~LightComponent() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;

	public:
		LightType GetLightType() const { return m_LightType; }
		virtual LightCB GetLightCB() const = 0;

		const Vec3& GetLightColor() const { return m_LightColor; }
		void SetLightColor(const Vec3& color) { m_LightColor = color; }

	protected:
		LightType m_LightType;
		Vec3 m_LightColor = { 1.0f, 1.0f, 1.0f };
	};

	class LightCount
	{
	public:
		LightCount();
		LightCount(int dLight, int pLight, int sLight);

		void AddLightCount(LightComponent::LightType type);

	private:
		int m_DLight = 0;
		int m_PLight = 0;
		int m_SLight = 0;
	};

	class DirectionalLightComponent : public LightComponent
	{
	public:
		DirectionalLightComponent(const Vec3 & color);

		virtual void InitializeDetailFunction() override;

		virtual LightCB GetLightCB() const override;
	};
}



