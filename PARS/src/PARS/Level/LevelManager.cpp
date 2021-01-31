#include "stdafx.h"
#include "PARS/Level/LevelManager.h"

namespace PARS
{
	void LevelManager::Update()
	{
		for (const auto& level : m_Levels)
		{
			level->Update();
		}

		std::vector<SPtr<Level>> deadLevels;
		for (auto& level : m_Levels)
		{
			if (level->GetLevelState() == Level::LevelState::Dead)
			{
				deadLevels.push_back(level);
			}
		}

		for (auto& level : deadLevels)
		{
			RemoveLevel(level);
		}
	}

	void LevelManager::Shutdown()
	{
		for (auto level : m_Levels)
		{
			if (level != nullptr)
			{
				level->Shutdown();
			}
		}
	}

	void LevelManager::AddLevel(const SPtr<Level>& level)
	{
		m_Levels.emplace_back(level);
	}

	void LevelManager::RemoveLevel(const WPtr<Level>& level)
	{
		auto iter = std::find_if(m_Levels.begin(), m_Levels.end(),
			[&level](const WPtr<Level>& ly)
			{return level.lock() == ly.lock(); });
		if (iter != m_Levels.end())
		{
			level.lock()->Shutdown();
			m_Levels.erase(iter);
		}
	}
}