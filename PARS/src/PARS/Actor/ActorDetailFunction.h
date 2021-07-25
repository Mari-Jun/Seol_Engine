#pragma once
#include "PARS/Actor/Actor.h"
#include "PARS/Layer/DetailFunction.h"

namespace PARS
{
	class Actor;

	class ActorDetailFunction : public DetailFunction
	{
	public:
		ActorDetailFunction() = default;

		virtual void Initialize(const WPtr<Actor>& owner);

	public:
		void TransformDetail();
		virtual void PositionDetail(const SPtr<Actor>& owner);
		virtual void RotationDetail(const SPtr<Actor>& owner);
		virtual void ScaleDetail(const SPtr<Actor>& owner);

	private:
		WPtr<Actor> m_Owner;
	};
}
