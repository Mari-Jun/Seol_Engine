#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class Component
	{
	public:
		Component(int updateOrder = 100);
		virtual ~Component() = default;

		virtual void Initialize() {}
		virtual void Shutdown() {}
		virtual void Update(float deltaTime) {}
		virtual void Draw() {}
		virtual void UpdateWorldMatrix() {}

	protected:
		int m_UpdateOrder;
	};
}


