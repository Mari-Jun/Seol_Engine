#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Layer/DetailFunction.h"

namespace PARS
{
	class Component;

	class ComponentDetailFunction : public DetailFunction
	{
	public:
		ComponentDetailFunction() = default;

		void Initialize(const WPtr<Actor>& owner, const WPtr<Component>& comp);

	protected:
		WPtr<Component> m_Component;
	};
}


