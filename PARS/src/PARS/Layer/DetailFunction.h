#pragma once
#include "imgui.h"

namespace PARS
{
	class Actor;

	class DetailFunction
	{
	public:
		DetailFunction() = default;

		void Initialize(const WPtr<Actor>& owner);
		virtual void AddFunctionInfo() {}

	protected:
		WPtr<Actor> m_Owner;

	protected:
		ImVec4 m_TextColor = { 0.0f, 1.0f, 1.0f, 1.0f };

	};
}

