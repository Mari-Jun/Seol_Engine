#include "stdafx.h"
#include "PARS/Layer/Layer.h"

namespace PARS
{
	Layer::Layer(const std::string& name)
		: m_LayerName(name)
		, m_LayerState(LayerState::Active)
	{
	}

	Layer::~Layer()
	{
	}
}
