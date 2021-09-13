#include "stdafx.h"
#include "PARS/Actor/Controller/Controller.h"

namespace PARS
{
	Controller::Controller(const std::string& name)
		: Actor(name)
	{
	}

	Controller::Controller(const SPtr<Pawn>& pawn, const std::string& name)
		: Actor(name)
		, m_ControlledPawn(pawn)
	{
	}
}
