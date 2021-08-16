#pragma once
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunction.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailHelper.h"

namespace PARS
{
	class Component;

	class ComponentDetailFunction : public DetailFunction
	{
	public:
		ComponentDetailFunction() = default;

		void Initialize(const WPtr<Component>& comp);
		virtual void CreateFunctionInfos() {}

	protected:
		WPtr<Component> m_Component;
	};
}


