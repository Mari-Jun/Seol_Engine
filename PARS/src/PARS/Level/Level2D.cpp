#include "stdafx.h"
#include "PARS/Level/Level2D.h"
#include "PARS/Core/Window.h"
#include "PARS/Actor/Pawn.h"
#include "PARS/Actor/Controller/PlayerController.h"
#include "PARS/Input/Input.h"
#include "PARS/Renderer/Core/RenderFactory.h"

namespace PARS
{
	Level2D::Level2D(const std::string& name)
		: Level(name)
	{
	}

	void Level2D::InitializeLevel()
	{
		auto defualtActor = CreateSPtr<Pawn>();
		defualtActor->SetPosition({ 0.0f, 0.0f, -0.1f });
		m_DefaultCamera = CreateSPtr<CameraComponent>();
		defualtActor->AddComponent(m_DefaultCamera);
		AddActor(defualtActor);

		m_DefaultController = CreateSPtr<PlayerController>(defualtActor);
		m_DefaultController->SetUseDefaultKeyEvent(true);
		m_DefaultController->SetUseDefaultMouseEvent(false);
		AddActor(m_DefaultController);

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
		m_DefaultCamera->SetCameraState(CameraComponent::CameraState::Active);
	}

	void Level2D::SetDefaultCameraPause()
	{
		m_DefaultCamera->SetCameraState(CameraComponent::CameraState::Paused);
	}
}