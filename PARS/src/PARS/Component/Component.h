#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class Actor;

	class Component : public std::enable_shared_from_this<Component>
	{
	public:
		Component(int updateOrder = 100);
		virtual ~Component() = default;

		virtual void Initialize() {}
		virtual void Shutdown() {}
		virtual void Update(float deltaTime) {}
		virtual void UpdateWorldMatrix() {}

	public:
		void SetOwner(const WPtr<Actor>& owner) { m_Owner = owner; }
		const WPtr<Actor>& GetOwner() const { return m_Owner; }

	protected:
		WPtr<Actor> m_Owner;
		int m_UpdateOrder;
	};
}


