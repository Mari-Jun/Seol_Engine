#pragma once
#include "PARS/Component/ComponentDetailFunction.h"
#include "PARS/Component/Camera/Perspective/PerspectiveCameraComp.h"

namespace PARS
{
	class PerspectiveCameraCompDetailFunction : public ComponentDetailFunction
	{
	public:
		PerspectiveCameraCompDetailFunction() = default;

		virtual void CreateFunctionInfos() override;

	private:
		void CameraSettingDetail(const SPtr<PerspectiveCameraComponent>& comp);
	};
}
