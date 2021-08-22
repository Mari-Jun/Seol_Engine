#include "stdafx.h"
#include "PARS/Component/Camera/CameraComponent.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Actor/Actor.h"

namespace PARS
{
	CameraComponent::CameraComponent(const std::string& name)
		: Component(name)
		, m_CameraState(CameraState::Active)
		, m_ViewMatrix(Mat4::Identity)
		, m_Projection(Mat4::Identity)
	{
	}

	void CameraComponent::Initialize()
	{
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->AddCameraComponent(std::reinterpret_pointer_cast<CameraComponent>(shared_from_this()));
	}

	void CameraComponent::Shutdown()
	{
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->RemoveCameraComponent(std::reinterpret_pointer_cast<CameraComponent>(shared_from_this()));
	}

	void CameraComponent::Update(float deltaTime)
	{
		
	}

	void CameraComponent::UpdateWorldMatrix()
	{
		if (IsActive())
		{
			const auto& owner = m_Owner.lock();

			Vec3 eye = owner->GetPosition();
			Vec3 target = eye + owner->GetForward() * 100.0f;
			Vec3 up = owner->GetUp();

			m_ViewMatrix = Mat4::LookAt(eye, target, up);
		}
	}
}
