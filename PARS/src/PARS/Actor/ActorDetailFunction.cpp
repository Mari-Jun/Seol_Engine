#include "stdafx.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Actor/ActorDetailFunction.h"

namespace PARS
{
	void ActorDetailFunction::Initialize(const WPtr<Actor>& owner)
	{
		m_Owner = owner;
		Initailize(m_Owner.lock()->GetNameOfClass());
		CreateFunctionInfos();
	}

	void ActorDetailFunction::CreateFunctionInfos()
	{
		AddFunctionInfo(FunctionInfo{ "Transform", [this]() {TransformDetail(); }});
	}

	void ActorDetailFunction::TransformDetail()
	{
		const auto& owner = m_Owner.lock();
		PositionDetail(owner);
		RotationDetail(owner);
		ScaleDetail(owner);
	}

	void ActorDetailFunction::PositionDetail(const SPtr<Actor>& owner)
	{
		Vec3 pos = owner->GetPosition();
		ImGui::DragFloat3("Position", (float*)&pos, 0.5f, -FLT_MAX, FLT_MAX, "%.4f");

		if (owner->GetPosition() != pos)
		{
			owner->SetPosition(pos);
		}
	}

	void ActorDetailFunction::RotationDetail(const SPtr<Actor>& owner)
	{
		Vec3 rotEuler = owner->GetRotation().QuatToEuler();
		ImGui::DragFloat3("Rotation", (float*)&rotEuler, 0.5f, -180.0f, 180.0f, "%.4f");
		Quaternion quat = Quaternion::Identity;
		quat *= Quaternion(Vec3::AxisZ, Math::ToRadians(rotEuler.z))
			* Quaternion(Vec3::AxisX, Math::ToRadians(rotEuler.x))
			* Quaternion(Vec3::AxisY, Math::ToRadians(rotEuler.y));

		if (owner->GetRotation() != quat)
		{
			owner->SetRotation(quat);
		}
	}

	void ActorDetailFunction::ScaleDetail(const SPtr<Actor>& owner)
	{
		Vec3 scale = owner->GetScale();
		ImGui::DragFloat3("Scale", (float*)&scale, 0.05f, 0.0f, FLT_MAX, "%.2f");

		if (owner->GetScale() != scale)
		{
			owner->SetScale(scale);
		}
	}
}