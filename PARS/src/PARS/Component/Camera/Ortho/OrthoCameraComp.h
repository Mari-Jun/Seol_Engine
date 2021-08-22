#pragma once
#include "PARS/Component/Camera/CameraComponent.h"

namespace PARS
{
	class OrthoCameraComponent : public CameraComponent
	{
	public:
		OrthoCameraComponent();
		virtual ~OrthoCameraComponent() = default;

		virtual void InitializeDetailFunction() override;

		virtual void UpdateProjection(float width, float height) override;

	private:
		float m_OrthoWidth = 512.0f;

	public:
		float GetOrthoWidth() const { return m_OrthoWidth; }
		void SetOrthoWidth(float width) { m_OrthoWidth = width; }
	};
}
