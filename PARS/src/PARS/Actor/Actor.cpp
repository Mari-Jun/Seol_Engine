#include "stdafx.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	Actor::Actor()
		: m_ActorState(ActorState::Active)
	{
		m_ComponentManager = CreateUPtr<ComponentManager>();
	}

	void Actor::InitializeActor()
	{
		Initialize();
	}

	void Actor::ShutdownActor()
	{
		Shutdown();
		m_ComponentManager->Shutdown();
	}

	void Actor::UpdateActor(float deltaTime)
	{
		UpdateWorldMatrix();

		m_ComponentManager->Update(deltaTime);
		Update(deltaTime);
		
		UpdateWorldMatrix();
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

	void Actor::AddComponent(const SPtr<class Component>& component)
	{
		m_ComponentManager->AddComponent(component);
		component->SetOwner(weak_from_this());
	}
}
