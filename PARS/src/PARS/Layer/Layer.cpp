#include "stdafx.h"
#include "PARS/Layer/Layer.h"
#include "PARS/Level/LevelManager.h"

namespace PARS
{
	Layer::Layer(const std::string& name)
		: m_LayerName(name)
		, m_LayerState(LayerState::Active)
	{
	}

	void Layer::AddLevel(const SPtr<class Level>& level)
	{
		auto levelManger = LevelManager::GetLevelManager();
		levelManger->OpenLevel(level);
	}
}
