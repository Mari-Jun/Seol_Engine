#include "stdafx.h"
#include "PARS/Level/Level2D.h"
#include "PARS/Core/Window.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Renderer/Core/RenderFactory.h"

namespace PARS
{
	Level2D::Level2D(const std::string& name)
		: Level(name)
	{
	}

	void Level2D::InitializeLevel()
	{
		auto actor = CreateSPtr<Actor>();
		actor->SetPosition({ 0.0f, 0.0f, -0.1f });
		m_Camera = CreateSPtr<CameraComponent>();
		actor->AddComponent(m_Camera);
		AddActor(actor);

		float width = static_cast<float>(Window::GetWindowInfo()->m_Width) / 2;
		float height = static_cast<float>(Window::GetWindowInfo()->m_Height) / 2;

		SetRenderProjectionOrtho(-width, width, -height, height);
	}

	void Level2D::SetRenderProjectionOrtho(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 projection = Mat4::Ortho(left, right, bottom, top, near, far);
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->SetProjection(projection);
	}

	void Level2D::SetDefaultCameraActive()
	{
		m_Camera->SetCameraState(CameraComponent::CameraState::Active);
	}

	void Level2D::SetDefaultCameraPause()
	{
		m_Camera->SetCameraState(CameraComponent::CameraState::Paused);
	}
}