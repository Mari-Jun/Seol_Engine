#pragma once

#include "PARS/Component/ComponentDetailFunction.h"	
#include "PARS/Component/Light/LightComponent.h"

namespace PARS
{
	class DLightCompDetailFunction : public ComponentDetailFunction
	{
	public:
		DLightCompDetailFunction() = default;

		virtual void CreateFunctionInfos() override;

	private:
		void LightDetail();
		void LightColor(const SPtr<DirectionalLightComponent>& light);

	};
}


