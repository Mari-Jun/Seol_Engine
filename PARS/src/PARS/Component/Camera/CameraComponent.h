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

	public:
		CameraComponent(const std::string& name = "Camera Component");
		virtual ~CameraComponent() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(float deltaTime) override;
		virtual void UpdateWorldMatrix() override;

		virtual void UpdateProjection(float width, float height) = 0;

	protected:
		CameraState m_CameraState;
		Mat4 m_ViewMatrix;
		Mat4 m_Projection;
		bool m_IsUpdateProjection;

	public:
		const Mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const Mat4& GetProjection() const { return m_Projection; }
		void ChangeProjectionInfo() { m_IsUpdateProjection = true; }
		bool IsUpdateProjection() const { return m_IsUpdateProjection; }

		void SetCameraState(CameraState state) { m_CameraState = state; }
		bool IsActive() const { return m_CameraState == CameraState::Active; }
	};
}


