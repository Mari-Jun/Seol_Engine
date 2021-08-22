#include "stdafx.h"
#include "PARS/Component/Camera/Ortho/OrthoCameraDF.h"

namespace PARS
{
	void OrthoCameraCompDetailFunction::CreateFunctionInfos()
	{
		const auto& comp = std::reinterpret_pointer_cast<OrthoCameraComponent>(m_Component.lock());
		if (comp != nullptr)
		{
			comp->AddDetailFunctionInfo(FunctionInfo{ "Camera Setting", [this, comp]() { CameraSettingDetail(comp); } });
		}
	}

	void OrthoCameraCompDetailFunction::CameraSettingDetail(const SPtr<OrthoCameraComponent>& comp)
	{
		float width = comp->GetOrthoWidth();
		ImGui::DragFloat("Ortho Width", &width, 10.0f, -FLT_MAX, FLT_MAX, "%.5f");
		if (width != comp->GetOrthoWidth())
		{
			comp->SetOrthoWidth(width);
			comp->ChangeProjectionInfo();
		}
	}
}
