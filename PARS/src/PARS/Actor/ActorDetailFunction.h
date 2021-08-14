#pragma once
#include "imgui.h"

namespace PARS
{
	class Actor;

	class ActorDetailFunction
	{
	public:
		ActorDetailFunction() = default;

		void Initialize(const WPtr<Actor>& owner);
		virtual void AddFunctionInfo();

	protected:
		WPtr<Actor> m_Owner;
		ImVec4 m_TextColor = { 0.0f, 1.0f, 1.0f, 1.0f };

	protected:
		void TransformDetail();
		virtual void PositionDetail(const SPtr<Actor>& owner);
		virtual void RotationDetail(const SPtr<Actor>& owner);
		virtual void ScaleDetail(const SPtr<Actor>& owner);
	};
}
