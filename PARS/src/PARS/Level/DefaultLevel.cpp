#include "stdafx.h"
#include "PARS/Level/DefaultLevel.h"
#include "PARS/Core/Window.h"
#include "PARS/Layer/DetailLayer.h"
#include "PARS/Actor/Pawn/Pawn.h"
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
		m_DetailLayer = CreateSPtr<DetailLayer>("Detail Layer");
		m_DetailLayer->OnDestroy([this]() {Destroy(); });
		AddLayer(m_DetailLayer);

		m_DefaultPawn = CreateSPtr<Pawn>("DefaultPawn");
		m_DefaultPawn->SetPosition({ 0.0f, 0.0f, -0.1f });
		AddActor(m_DefaultPawn);

		m_DefaultController = CreateSPtr<PlayerController>(m_DefaultPawn);
		m_DefaultCamera = CreateSPtr<CameraComponent>();
		m_DefaultPawn->AddComponent(m_DefaultCamera);
		AddActor(m_DefaultController);
	}

	void DefaultLevel::AddActor(const SPtr<class Actor>& actor)
	{
		Level::AddActor(actor);
		if (m_DetailLayer != nullptr)
		{
			m_DetailLayer->AddObjectToLayer(DetailObject{ actor->GetActorName(), actor->GetDetailFunctionInfos() });
		}
	}

	void DefaultLevel::RemoveActor(const SPtr<class Actor>& actor)
	{
		Level::RemoveActor(actor);
		if (m_DetailLayer != nullptr)
		{
			
		}
	}

	void DefaultLevel::SetDefaultCameraActive()
	{
		m_DefaultCamera->SetCameraState(CameraComponent::CameraState::Active);
	}

	void DefaultLevel::SetDefaultCameraPause()
	{
		m_DefaultCamera->SetCameraState(CameraComponent::CameraState::Paused);
	}

	Level2D::Level2D(const std::string& name)
		: DefaultLevel(name)
	{
	}

	void Level2D::InitializeLevel()
	{
		DefaultLevel::InitializeLevel();

		m_DefaultController->AddAxisAction("Move Rightward",
			std::vector{ KeyAxis{PARS_KEY_D, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_A, -1.0f, PARS_MOUSE_RBUTTON} },
			[this](float axis) {m_DefaultController->MoveRightward(axis); });
		m_DefaultController->AddAxisAction("Move Upward",
			std::vector{ KeyAxis{PARS_KEY_W, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_S, -1.0f, PARS_MOUSE_RBUTTON} },
			[this](float axis) {m_DefaultController->MoveUpward(axis); });

		SetDefaultControllerKeyEvent(true);
		SetDefaultControllerMouseEvent(false);

		float width = static_cast<float>(Window::GetWindowInfo()->m_Width - Window::GetWindowInfo()->m_LayerWidth) / 2;
		float height = static_cast<float>(Window::GetWindowInfo()->m_Height) / 2;

		SetRenderProjectionOrtho(-width, width, -height, height);
	}

	void Level2D::SetDefaultControllerKeyEvent(bool use)
	{
		m_DefaultController->ActiveAction(ActionType::Axis, "Move Rightward", use);
		m_DefaultController->ActiveAction(ActionType::Axis, "Move Upward", use);
	}

	void Level2D::SetDefaultControllerMouseEvent(bool use)
	{
	
	}

	void Level2D::SetRenderProjectionOrtho(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 projection = Mat4::Ortho(left, right, bottom, top, near, far);
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->SetProjection(projection);
	}	

	Level3D::Level3D(const std::string& name)
		: DefaultLevel(name)
	{
	}

	void Level3D::InitializeLevel()
	{
		DefaultLevel::InitializeLevel();

		m_DefaultController->AddAxisAction("Move Forward",
			std::vector{ KeyAxis{PARS_KEY_W, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_S, -1.0f, PARS_MOUSE_RBUTTON} },
			[this](float axis) {m_DefaultController->MoveForward(axis); });
		m_DefaultController->AddAxisAction("Move Rightward",
			std::vector{ KeyAxis{PARS_KEY_D, 1.0f , PARS_MOUSE_RBUTTON}, KeyAxis{PARS_KEY_A, -1.0f, PARS_MOUSE_RBUTTON} },
			[this](float axis) {m_DefaultController->MoveRightward(axis); });
		m_DefaultController->AddAxisAction("Move Upward",
			std::vector{ KeyAxis{PARS_KEY_E, 1.0f, PARS_MOUSE_RBUTTON }, KeyAxis{PARS_KEY_Q, -1.0f, PARS_MOUSE_RBUTTON} },
			[this](float axis) {m_DefaultController->MoveUpward(axis); });
		m_DefaultController->AddOnceAction("Mouse RButton", PARS_MOUSE_RBUTTON, [this]() {Input::SetCursorHide(true); });
		m_DefaultController->AddReleaseAction("Mouse RButton", PARS_MOUSE_RBUTTON, [this]() {Input::SetCursorHide(false); });

		/*m_DefaultController->AddAxisAction("Turn Yaw",
			std::vector{ KeyAxis{PARS_KEY_Q, -1.0f , PARS_MOUSE_RBUTTON}, KeyAxis{PARS_KEY_E, 1.0f, PARS_MOUSE_RBUTTON} },
			[this](float axis) {m_DefaultController->TurnAxisY(axis); });*/
		

		SetDefaultControllerKeyEvent(true);
		SetDefaultControllerMouseEvent(false);

		float width = static_cast<float>(Window::GetWindowInfo()->m_Width - Window::GetWindowInfo()->m_LayerWidth) / 2;
		float height = static_cast<float>(Window::GetWindowInfo()->m_Height) / 2;

		SetRenderProjectionPerspective(Math::ToRadians(70.0f), width / height);
	}

	void Level3D::SetDefaultControllerKeyEvent(bool use)
	{
		m_DefaultController->ActiveAction(ActionType::Axis, "Move Forward", use);
		m_DefaultController->ActiveAction(ActionType::Axis, "Move Rightward", use);
		m_DefaultController->ActiveAction(ActionType::Axis, "Move Upward", use);
		m_DefaultController->ActiveAction(ActionType::Axis, "Turn Yaw", use);
	}

	void Level3D::SetDefaultControllerMouseEvent(bool use)
	{
	}

	void Level3D::SetRenderProjectionPerspective(float fovy, float aspect, float near, float far)
	{
		Mat4 projection = Mat4::Perspective(fovy, aspect, near, far);
		const auto& factory = RenderFactory::GetRenderFactory();
		factory->SetProjection(projection);
	}
}