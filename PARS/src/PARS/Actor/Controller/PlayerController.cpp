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
		
	}

	void PlayerController::Update(float deltaTime)
	{
		SetPosition(m_ControlledPawn->GetPosition());
		

		//폰의 회전방향을 컨트롤러와 맞춘다.
		if (b_IsSameRotationWithPawn)
		{
			SetRotation(m_ControlledPawn->GetRotation());
		}
	}

	void PlayerController::MoveForward(float axis)
	{
		auto speed = m_ControlledPawn->GetMoveSpeed();
		m_ControlledPawn->GetMovementComp()->SetForwardSpeed(axis * speed);
	}

	void PlayerController::MoveRightward(float axis)
	{
		auto speed = m_ControlledPawn->GetMoveSpeed();
		m_ControlledPawn->GetMovementComp()->SetRightSpeed(axis * speed);
	}

	void PlayerController::MoveUpward(float axis)
	{
		auto speed = m_ControlledPawn->GetMoveSpeed();
		m_ControlledPawn->GetMovementComp()->SetUpSpeed(axis * speed);
	}

	void PlayerController::TurnAxisY(float axis)
	{
		auto speed = Math::PiDiv2;
		m_ControlledPawn->GetMovementComp()->SetYawSpeed(axis * speed);
	}

	void PlayerController::TurnAxisX(float axis)
	{
	}

	
}
