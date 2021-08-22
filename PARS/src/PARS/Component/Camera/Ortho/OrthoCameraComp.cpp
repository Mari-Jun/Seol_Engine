#include "stdafx.h"
#include "PARS/Component/Camera/Ortho/OrthoCameraComp.h"
#include "PARS/Component/Camera/Ortho/OrthoCameraDF.h"

namespace PARS
{
	OrthoCameraComponent::OrthoCameraComponent()
		: CameraComponent("Ortho Camera Component")
		, m_OrthoWidth(512.0f)
	{
	}

	void OrthoCameraComponent::InitializeDetailFunction()
	{
		m_CompDetailFunction = CreateUPtr<OrthoCameraCompDetailFunction>();
	}

	void OrthoCameraComponent::UpdateProjection(float width, float height)
	{
		m_Projection = Mat4::Ortho(-m_OrthoWidth, m_OrthoWidth, 
			-m_OrthoWidth / (width / height), m_OrthoWidth / (width / height), 0.0f, 10000.0f);
		m_IsUpdateProjection = false;
	}
}