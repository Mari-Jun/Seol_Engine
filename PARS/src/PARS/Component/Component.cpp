#include "stdafx.h"
#include "PARS/Component/Component.h"

namespace PARS
{
	Component::Component(const WPtr<Actor>& owner, int updateOrder)
		: m_Owner(owner)
		, m_UpdateOrder(updateOrder)
	{
	}
}
