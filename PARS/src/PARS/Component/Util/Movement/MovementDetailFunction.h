#pragma once

#include "PARS/Component/ComponentDetailFunction.h"	
#include "PARS/Component/Util/Movement/MovementComponent.h"

namespace PARS
{
	class MovementCompDetailFunction : public ComponentDetailFunction
	{
	public:
		MovementCompDetailFunction() = default;

		virtual void CreateFunctionInfos() override;

	private:
		void SpeedDetail(const SPtr<MovementComponent>& movementComp);

	};
}


