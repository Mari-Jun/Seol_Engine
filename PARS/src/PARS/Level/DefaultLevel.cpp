#include "stdafx.h"
#include "PARS/Level/DefaultLevel.h"
#include "PARS/Core/Window.h"
#include "PARS/Actor/Pawn.h"
#include "PARS/Actor/Controller/PlayerController.h"
#include "PARS/Input/Input.h"
#include "PARS/Renderer/Core/RenderFactory.h"

namespace PARS
{
	DefaultLevel::DefaultLevel(const std::string& name)
		: Level(name)
	{
	}

	void DefaultLevel::InitializeLevel()
	{
		m_DefaultPawn = CreateSPtr<Pawn>();
		m_DefaultPawn->SetPosition({ 0.0f, 0.0f, -0.1f });
		m_DefaultCamera = CreateSPtr<CameraComponent>();
		m_DefaultPawn->AddComponent(m_DefaultCamera);
		AddActor(m_DefaultPawn);

		m_DefaultController = CreateSPtr<PlayerController>(m_DefaultPawn);
		AddActor(m_DefaultController);
	}

	void DefaultLevel::SetDefaultCameraActive()
	{
		m_DefaultCamera->SetCameraState(CameraComponent::CameraState::Active);
	}

	void DefaultLevel::SetDefaultCameraPause()
	{
		m_DefaultCamera->SetCameraState(CameraComponent::CameraState::Paused);
	}

	void DefaultLevel::SetDefaultControllerKeyEvent(bool use)
	{
		m_DefaultController->SetUseDefaultKeyEvent(use);
	}

	void DefaultLevel::SetDefaultControllerMouseEvent(bool use)
	{
		m_DefaultController->SetUseDefaultMouseEvent(use);
	}

	Level2D::Level2D(const std::string& name)
		: DefaultLevel(name)
	{
	}

	void Level2D::InitializeLevel()
	{
		DefaultLevel::InitializeLevel();

		SetDefaultControllerKeyEvent(true);
		SetDefaultControllerMouseEvent(false);

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
}