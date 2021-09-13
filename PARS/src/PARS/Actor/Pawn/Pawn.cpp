#include "stdafx.h"
#include "PARS/Actor/Pawn/Pawn.h"
#include "PARS/Actor/Controller/Controller.h"

namespace PARS
{
	Pawn::Pawn(const std::string& name)
		: Actor(name)
	{
	}

	void Pawn::Initialize()
	{
		m_MovementComp = CreateSPtr<MovementComponent>();
		AddComponent(m_MovementComp);
	}

	void Pawn::Shutdown()
	{
	}
}