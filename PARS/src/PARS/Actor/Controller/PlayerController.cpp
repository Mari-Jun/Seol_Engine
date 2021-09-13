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
		TurnMouse();
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

	void PlayerController::TurnMouse()
	{
		if (Input::IsCursorHide())
		{
			auto pos = Input::GetRelativeMousePosition();
			m_MovementComp->SetYawSpeed(pos.x / 10.0f);
		
			auto vec = GetForward();
			vec.y = 0.0f;
			vec.Normalize();
			m_Pitch = Math::Acos(Vec3::Dot(GetForward(), vec));

			if (m_Pitch < Math::Pi / 3.0f || (GetForward().y > 0.0f && pos.y > 0.0f) || (GetForward().y < 0.0f && pos.y < 0.0f))
			{
				m_MovementComp->SetPitchSpeed(pos.y / 10.0f);

			}
			else
			{
				m_MovementComp->SetPitchSpeed(0.0f);
			}
		}		
		else
		{
			m_MovementComp->SetYawSpeed(0.0f);
			m_MovementComp->SetPitchSpeed(0.0f);
		}
	}	
}
