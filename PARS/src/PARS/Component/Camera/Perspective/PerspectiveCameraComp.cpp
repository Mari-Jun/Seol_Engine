#include "stdafx.h"
#include "PARS/Component/Camera/Perspective/PerspectiveCameraComp.h"
#include "PARS/Component/Camera/Perspective/PerspectiveCameraDF.h"

namespace PARS
{
	PerspectiveCameraComponent::PerspectiveCameraComponent()
		: CameraComponent("Perspective Camera Component")
	{
	}

	void PerspectiveCameraComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<PerspectiveCameraCompDetailFunction>();
	}

	void PerspectiveCameraComponent::UpdateProjection(float width, float height)
	{
		m_Projection = Mat4::Perspective(Math::ToRadians(m_Fovy), width / height, 0.1f, 100'000.0f);
		m_IsUpdateProjection = false;
	}
}
