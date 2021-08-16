#pragma once
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunction.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailHelper.h"


namespace PARS
{
	class Actor;

	class ActorDetailFunction : public DetailFunction
	{
	public:
		ActorDetailFunction() = default;

		void Initialize(const WPtr<Actor>& owner);
		virtual void CreateFunctionInfos();

	protected:
		WPtr<Actor> m_Owner;

	private:
		void TransformDetail();
		void PositionDetail(const SPtr<Actor>& owner);
		void RotationDetail(const SPtr<Actor>& owner);
		void ScaleDetail(const SPtr<Actor>& owner);
	};
}
