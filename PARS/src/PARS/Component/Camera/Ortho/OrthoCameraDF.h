#pragma once
#include "PARS/Component/ComponentDetailFunction.h"
#include "PARS/Component/Camera/Ortho/OrthoCameraComp.h"

namespace PARS
{
	class OrthoCameraCompDetailFunction : public ComponentDetailFunction
	{
	public:
		OrthoCameraCompDetailFunction() = default;

		virtual void CreateFunctionInfos() override;

	private:
		void CameraSettingDetail(const SPtr<OrthoCameraComponent>& comp);
	};
}

