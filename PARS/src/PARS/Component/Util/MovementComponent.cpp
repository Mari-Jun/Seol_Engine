#include "stdafx.h"
#include "PARS/Component/Util/MovementComponent.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	MovementComponent::MovementComponent(const std::string& name, int updateOrder)
		: Component(name, updateOrder)
		, m_ForwardSpeed(0.0f)
		, m_RightSpeed(0.0f)
		, m_UpSpeed(0.0f)
		, m_YawSpeed(0.0f)
		, m_PitchSpeed(0.0f)
	{
	}

	void MovementComponent::Update(float deltaTime)
	{
		if (!Math::NearZero(m_YawSpeed) ||
			!Math::NearZero(m_PitchSpeed))
		{
			auto owner = m_Owner.lock();
			Quaternion rotation = owner->GetRotation();	
			rotation *= Quaternion(Vec3::AxisY, m_YawSpeed * deltaTime);
			owner->SetRotation(rotation);
			rotation *= Quaternion(owner->GetRight(), m_PitchSpeed * deltaTime);
			owner->SetRotation(rotation);
			
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