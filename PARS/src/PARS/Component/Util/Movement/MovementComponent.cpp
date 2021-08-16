#include "stdafx.h"
#include "PARS/Component/Util/Movement/MovementComponent.h"
#include "PARS/Component/Util/Movement/MovementDetailFunction.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	MovementComponent::MovementComponent(const std::string& name, int updateOrder)
		: Component(name, updateOrder)
	{
	}

	void MovementComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<MovementCompDetailFunction>();
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
			pos += owner->GetForward() * m_ForwardSpeed * m_MaxSpeed * deltaTime;
			pos += owner->GetRight() * m_RightSpeed * m_MaxSpeed * deltaTime;
			pos += owner->GetUp() * m_UpSpeed * m_MaxSpeed * deltaTime;
			owner->SetPosition(pos);
		}
	}
}