#include "stdafx.h"
#include "PARS/Layer/Layer.h"
#include "PARS/Layer/LayerManager.h"
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

	void Layer::LoadLevel(const SPtr<class Level>& level)
	{
		auto levelManger = LevelManager::GetLevelManager();
		levelManger->OpenLevel(level);
		std::cout << level->GetFilePath() << std::endl;
		std::ifstream file{ level->GetFilePath() + level->GetExtension(), std::ios::binary };
		if (file.is_open())
		{
			level->LoadLevel(file);
		}
	}

	void Layer::AddLayer(const SPtr<Layer>& layer)
	{
		auto layerManger = LayerManager::GetLayerManager();
		layerManger->AddLayer(layer);
	}
}
