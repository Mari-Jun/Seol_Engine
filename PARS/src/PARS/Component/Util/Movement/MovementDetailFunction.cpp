#include "stdafx.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Component/Util/Movement/MovementDetailFunction.h"

namespace PARS
{
	void MovementCompDetailFunction::CreateFunctionInfos()
	{
		const auto& comp = std::reinterpret_pointer_cast<MovementComponent>(m_Component.lock());
		if (comp != nullptr)
		{
			comp->AddDetailFunctionInfo(FunctionInfo{ "Speed", [this, comp]() { SpeedDetail(comp); }});
		}
	}

	void MovementCompDetailFunction::SpeedDetail(const SPtr<MovementComponent>& movementComp)
	{
		float maxSpeed = movementComp->GetMaxSpeed();
		ImGui::DragFloat("Max Speed", &maxSpeed, 10.0f, 0, FLT_MAX, "%.5f");
		if (maxSpeed != movementComp->GetMaxSpeed())
		{
			movementComp->SetMaxSpeed(maxSpeed);
		}
	}
}
