#include "stdafx.h"
#include "PARS/Component/Util/MovementComponent.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	MovementComponent::MovementComponent(int updateOrder)
		: Component(updateOrder)
		, m_ForwardSpeed(0.0f)
		, m_RightSpeed(0.0f)
		, m_UpSpeed(0.0f)
		, m_YawSpeed(0.0f)
	{
	}

	void MovementComponent::Update(float deltaTime)
	{
		if (!Math::NearZero(m_YawSpeed))
		{
			Quaternion rotation = m_Owner.lock()->GetRotation();	
			m_Owner.lock()->SetRotation(rotation * Quaternion(Vec3::AxisY, m_YawSpeed * deltaTime));
		}

		if (!Math::NearZero(m_ForwardSpeed) ||
			!Math::NearZero(m_RightSpeed) ||
			!Math::NearZero(m_UpSpeed))
		{
			auto owner = m_Owner.lock();
			Vec3 pos = owner->GetPosition();
			pos += owner->GetForward() * m_ForwardSpeed * deltaTime;
			pos += owner->GetRight() * m_RightSpeed * deltaTime;
			pos += owner->GetUp() * m_UpSpeed * deltaTime;
			owner->SetPosition(pos);
		}
	}
}