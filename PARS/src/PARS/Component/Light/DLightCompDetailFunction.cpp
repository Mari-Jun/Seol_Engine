#include "stdafx.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Component/Component.h"
#include "PARS/Component/Light/DLightCompDetailFunction.h"

namespace PARS
{
	void DLightCompDetailFunction::AddFunctionInfo()
	{
		const auto& comp = m_Component.lock();
		m_Owner.lock()->AddDetailFunctionInfo(FunctionInfo{ comp->GetCompName(), [this]() { LightDetail(); } });
	}

	void DLightCompDetailFunction::LightDetail()
	{
		const auto& light = std::reinterpret_pointer_cast<DirectionalLightComponent>(m_Component.lock());
		if (light != nullptr)
		{
			LightColor(light);
		}
	}

	void DLightCompDetailFunction::LightColor(const SPtr<DirectionalLightComponent>& light)
	{
		Vec3 color = light->GetLightColor();

		ImGui::ColorEdit3("Light Color", (float*)&color);

		if (light->GetLightColor() != color)
		{
			light->SetLightColor(color);
		}
	}
}
