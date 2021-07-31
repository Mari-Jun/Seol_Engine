#pragma once
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunction.h"

namespace PARS
{
	class ActorDetailFunction : public DetailFunction
	{
	public:
		ActorDetailFunction() = default;

		virtual void AddFunctionInfo() override;

	protected:
		void TransformDetail();
		virtual void PositionDetail(const SPtr<Actor>& owner);
		virtual void RotationDetail(const SPtr<Actor>& owner);
		virtual void ScaleDetail(const SPtr<Actor>& owner);
	};
}
