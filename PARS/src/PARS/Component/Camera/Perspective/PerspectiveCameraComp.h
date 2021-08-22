#pragma once
#include "PARS/Component/Camera/CameraComponent.h"

namespace PARS
{
	class PerspectiveCameraComponent : public CameraComponent
	{
	public:
		PerspectiveCameraComponent();
		virtual ~PerspectiveCameraComponent() = default;

		virtual void InitializeDetailFunction() override;

		virtual void UpdateProjection(float width, float height) override;

	private:
		float m_Fovy = 45.0f;

	public:
		float GetFovy() const { return m_Fovy; }
		void SetFovy(float fovy) { m_Fovy = fovy; }
	};
}


