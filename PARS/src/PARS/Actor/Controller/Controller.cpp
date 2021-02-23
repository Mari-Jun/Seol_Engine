#include "stdafx.h"
#include "PARS/Actor/Controller/Controller.h"

namespace PARS
{
	Controller::Controller()
	{
	}

	Controller::Controller(const SPtr<Pawn>& pawn)
		: m_ControlledPawn(pawn)
	{
	}
}
