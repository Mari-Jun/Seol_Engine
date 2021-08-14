#pragma once
#include "imgui.h"

namespace PARS
{
	class Component;

	class ComponentDetailFunction
	{
	public:
		ComponentDetailFunction() = default;

		void Initialize(const WPtr<Component>& comp);
		virtual void AddFunctionInfo() {}

	protected:
		WPtr<Component> m_Component;
		ImVec4 m_TextColor = { 0.0f, 1.0f, 1.0f, 1.0f };
	};
}


