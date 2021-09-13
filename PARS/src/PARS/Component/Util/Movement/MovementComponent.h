#pragma once
#include "PARS/Component/Component.h"

namespace PARS
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(const std::string& name = "MovementComponent", int updateOrder = 10);
		virtual ~MovementComponent() = default;

		virtual void InitializeDetailFunction() override;

		virtual void Update(float deltaTime) override;

	public:
		void SetMaxSpeed(float speed) { m_MaxSpeed = speed; }
		float GetMaxSpeed() const { return m_MaxSpeed; }

	protected:
		float m_MaxSpeed = 600.0f;

	public:
		void SetForwardSpeed(float speed) { m_ForwardSpeed = speed; }
		void SetRightSpeed(float speed) { m_RightSpeed = speed; }
		void SetUpSpeed(float speed) { m_UpSpeed = speed; }
		void SetYawSpeed(float speed) { m_YawSpeed = speed; }
		void SetPitchSpeed(float speed) { m_PitchSpeed = speed; }

	protected:
		float m_ForwardSpeed = 0.0f;
		float m_RightSpeed = 0.0f;
		float m_UpSpeed = 0.0f;
		float m_YawSpeed = 0.0f;
		float m_PitchSpeed = 0.0f;
	};

}

