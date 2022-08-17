#include "stdafx.h"
#include "PARS/GameState/GameState.h"
#include "PARS/Actor/Pawn/DefaultPawn.h"
#include "PARS/Actor/Controller/PlayerController.h"

namespace PARS
{
	void GameState::Shutdown()
	{
		m_DefaultPawn = nullptr;
		m_DefaultController = nullptr;
	}

	void Default2DGameState::Initialize()
	{
		m_DefaultPawn = CreateSPtr<DefaultPawn2D>("Default Pawn");
		m_DefaultPawn->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
		m_DefaultController = CreateSPtr<PlayerController2D>(m_DefaultPawn);
	}

	void Default3DGameState::Initialize()
	{
		m_DefaultPawn = CreateSPtr<DefaultPawn3D>("Default Pawn");
		m_DefaultPawn->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
		m_DefaultController = CreateSPtr<PlayerController3D>(m_DefaultPawn);
	}
}
