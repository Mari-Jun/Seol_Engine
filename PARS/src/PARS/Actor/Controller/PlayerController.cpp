#include "stdafx.h"
#include "PARS/Actor/Controller/PlayerController.h"

namespace PARS
{
	PlayerController::PlayerController(const std::string& name)
		: Controller(name)
	{
	}

	PlayerController::PlayerController(const SPtr<Pawn>& pawn, const std::string& name)
		: Controller(pawn, name)
	{

	}

	void PlayerController::Initialize()
	{
		SetFunctionVisibleState("Transform", FVS::Disabled);
		m_MovementComp = CreateSPtr<MovementComponent>();
		AddComponent(m_MovementComp);
		m_MovementComp->SetDetailVisibleState(DVS::Hide);
	}

	void PlayerController::ActorInput()
	{
	}

	void PlayerController::Update(float deltaTime)
	{
		//폰의 회전방향을 컨트롤러와 맞춘다.
		if (b_IsSameRotationWithPawn)
		{
			m_ControlledPawn->SetRotation(GetRotation());
		}
	}

	void PlayerController::MoveForward(float axis)
	{
		m_ControlledPawn->GetMovementComp()->SetForwardSpeed(axis);
	}

	void PlayerController::MoveRightward(float axis)
	{
		m_ControlledPawn->GetMovementComp()->SetRightSpeed(axis);
	}

	void PlayerController::MoveUpward(float axis)
	{
		m_ControlledPawn->GetMovementComp()->SetUpSpeed(axis);
	}

	void PlayerController::Turn(float axis)
	{
		auto pos = Input::GetRelativeMousePosition();
		m_MovementComp->SetYawSpeed((pos.x / 10.0f) * axis);
	}

	void PlayerController::LookUp(float axis)
	{
		auto vec = GetForward();
		vec.y = 0.0f;
		vec.Normalize();
		auto pitch = Math::Acos(Vec3::Dot(GetForward(), vec));

		auto pos = Input::GetRelativeMousePosition();

		if (pitch < Math::Pi / 3.0f || (GetForward().y > 0.0f && pos.y > 0.0f) || (GetForward().y < 0.0f && pos.y < 0.0f))
		{
			m_MovementComp->SetPitchSpeed((pos.y / 10.0f) * axis);
		}
		else
		{
			m_MovementComp->SetPitchSpeed(0.0f);
		}
	}

	PlayerController2D::PlayerController2D(const std::string& name)
		: PlayerController(name)
	{
	}

	PlayerController2D::PlayerController2D(const SPtr<class Pawn>& pawn, const std::string& name)
		: PlayerController(pawn, name)
	{
	}

	void PlayerController2D::Initialize()
	{
		PlayerController::Initialize();

		AddAxisAction("Move Rightward", std::vector{ KeyAxis{PARS_KEY_D, 1.0f}, KeyAxis{PARS_KEY_A, -1.0f} },
			[this](float axis) {MoveRightward(axis); });
		AddAxisAction("Move Upward", std::vector{ KeyAxis{PARS_KEY_W, 1.0f }, KeyAxis{PARS_KEY_S, -1.0f} },
			[this](float axis) {MoveUpward(axis); });
	}

	PlayerController3D::PlayerController3D(const std::string& name)
		: PlayerController(name)
	{
	}

	PlayerController3D::PlayerController3D(const SPtr<class Pawn>& pawn, const std::string& name)
		: PlayerController(pawn, name)
	{
	}

	void PlayerController3D::Initialize()
	{
		PlayerController::Initialize();

		AddAxisAction("Move Forward", std::vector{ KeyAxis{PARS_KEY_W, 1.0f}, KeyAxis{PARS_KEY_S, -1.0f} },
			[this](float axis) {MoveForward(axis); });
		AddAxisAction("Move Rightward", std::vector{ KeyAxis{PARS_KEY_D, 1.0f}, KeyAxis{PARS_KEY_A, -1.0f} },
			[this](float axis) {MoveRightward(axis); });
		AddAxisAction("Move Upward", std::vector{ KeyAxis{PARS_KEY_E, 1.0f }, KeyAxis{PARS_KEY_Q, -1.0f} },
			[this](float axis) {MoveUpward(axis); });
		AddAxisAction("Turn", std::vector{ KeyAxis{PARS_MOUSE_XMOVE, 1.0f} },
			[this](float axis) {Turn(axis); });
		AddAxisAction("LookUp", std::vector{ KeyAxis{PARS_MOUSE_YMOVE, 1.0f} },
			[this](float axis) {LookUp(axis); });
	}
}
