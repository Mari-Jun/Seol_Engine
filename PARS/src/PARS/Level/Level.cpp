#include "stdafx.h"
#include "PARS/Level/Level.h"

namespace PARS
{
	Level::Level(const std::string& name)
		: m_LevelName(name)
		, m_LevelState(LevelState::Active)
	{
	}

	Level::~Level()
	{
	}
}
