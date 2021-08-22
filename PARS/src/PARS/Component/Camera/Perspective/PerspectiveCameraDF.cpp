#include "stdafx.h"
#include "PARS/Component//Camera/Perspective/PerspectiveCameraDF.h"

namespace PARS
{
	void PerspectiveCameraCompDetailFunction::CreateFunctionInfos()
	{
		const auto& comp = std::reinterpret_pointer_cast<PerspectiveCameraComponent>(m_Component.lock());
		if (comp != nullptr)
		{
			comp->AddDetailFunctionInfo(FunctionInfo{ "Camera Setting", [this, comp]() { CameraSettingDetail(comp); } });
		}
	}

	void PerspectiveCameraCompDetailFunction::CameraSettingDetail(const SPtr<PerspectiveCameraComponent>& comp)
	{
		float fov = comp->GetFovy();
		ImGui::DragFloat("Field of view", &fov, 1.0f, 5.0f, 170.0f, "%.5f");
		if (fov != comp->GetFovy())
		{
			comp->SetFovy(fov);
			comp->ChangeProjectionInfo();
		}
	}
}
