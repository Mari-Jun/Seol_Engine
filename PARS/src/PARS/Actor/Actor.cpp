#include "stdafx.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	Actor::Actor()
		: m_ActorState(ActorState::Active)
	{
	}

	void Actor::Update(float deltaTime)
	{
		UpdateWorldMatrix();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
		
		UpdateWorldMatrix();
	}

	void Actor::UpdateComponents(float deltaTime)
	{

	}

	void Actor::UpdateWorldMatrix()
	{
		if (m_RechangeWorldMatrix)
		{
			//Change Actor World Matrix
			m_WorldMatrix = Mat4::CreateScale(m_Scale);
			m_WorldMatrix *= Mat4::CreateRotationFromQuaternion(m_Rotation);
			m_WorldMatrix *= Mat4::CreateTranslation(m_Position);

			//Change Component World Matrix

			m_RechangeWorldMatrix = false;
		}
	}
}
