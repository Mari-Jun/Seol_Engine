#pragma once
#include "PARS/Component/Component.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	class CameraComponent : public Component
	{
	public:
		enum class CameraState
		{
			Active,
			Paused
		};

		enum class CameraType
		{
			Default,
		};

	public:
		CameraComponent();
		virtual ~CameraComponent() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(float deltaTime) override;

	protected:
		CameraState m_CameraState;
		CameraType m_CameraType;
		Mat4 m_ViewMatrix;

	public:
		const Mat4& GetViewMatrix() const { return m_ViewMatrix; }

		void SetCameraState(CameraState state) { m_CameraState = state; }
		bool IsActive() const { return m_CameraState == CameraState::Active; }
	};
}


