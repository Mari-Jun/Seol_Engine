#include "stdafx.h"
#include "PARS/Actor/Controller/PlayerController.h"

namespace PARS
{
	PlayerController::PlayerController()
		: Controller()
	{
	}

	PlayerController::PlayerController(const SPtr<Pawn>& pawn)
		: Controller(pawn)
	{

	}

	void PlayerController::Initialize()
	{
		AddAxisAction("Move Forward", std::vector{ KeyAxis{PARS_KEY_W, 1.0f }, KeyAxis{PARS_KEY_S, -1.0f} }, [this](float axis) {MoveForward(axis); });
		AddAxisAction("Move Rightward", std::vector{ KeyAxis{PARS_KEY_D, 1.0f }, KeyAxis{PARS_KEY_A, -1.0f} }, [this](float axis) {MoveRightward(axis); });
	}

	void PlayerController::Update(float deltaTime)
	{
		SetPosition(m_ControlledPawn->GetPosition());

		//폰의 회전방향을 컨트롤러와 맞춘다.
	}

	void PlayerController::SetUseDefaultKeyEvent(bool use)
	{
		ActiveAction(ActionType::Axis, "Move Forward", use);
		ActiveAction(ActionType::Axis, "Move Rightward", use);
	}

	void PlayerController::SetUseDefaultMouseEvent(bool use)
	{
	}

	void PlayerController::MoveForward(float axis)
	{
		auto speed = m_ControlledPawn->GetMoveSpeed();
		m_ControlledPawn->GetMovementComp()->SetUpSpeed(axis * speed);
	}

	void PlayerController::MoveRightward(float axis)
	{
		auto speed = m_ControlledPawn->GetMoveSpeed();
		m_ControlledPawn->GetMovementComp()->SetRightSpeed(axis * speed);
	}
}
