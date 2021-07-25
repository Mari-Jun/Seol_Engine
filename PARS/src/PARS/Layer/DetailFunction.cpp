#include "stdafx.h"
#include "PARS/Actor/Actor.h"
#include "PARS/Layer/DetailFunction.h"

namespace PARS
{
	void DetailFunction::Initialize(const WPtr<Actor>& owner)
	{
		m_Owner = owner;
		AddFunctionInfo();
	}
}


