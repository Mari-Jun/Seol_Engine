#include "stdafx.h"
#include "PARS/Level/LevelManager.h"

namespace PARS
{
	LevelManager::LevelManager()
	{
		s_Instance = this;
	}

	void LevelManager::ProcessInput()
	{
		for (const auto& level : m_Levels)
		{
			if (level->GetLevelState() == Level::LevelState::Active)
			{
				level->LevelInput();
			}
		}
	}

	void LevelManager::Update(float deltaTime)
	{
		for (const auto& level : m_Levels)
		{
			if (level->GetLevelState() == Level::LevelState::Active)
			{
				level->Update(deltaTime);
			}
		}

		std::vector<SPtr<Level>> deadLevels;
		for (auto level : m_Levels)
		{
			if (level->GetLevelState() == Level::LevelState::Dead)
			{
				deadLevels.emplace_back(level);
			}
		}

		for (auto level : deadLevels)
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
		level->Initialize();
	}

	void LevelManager::RemoveLevel(const WPtr<Level>& level)
	{
		auto iter = std::find_if(m_Levels.begin(), m_Levels.end(),
			[&level](const WPtr<Level>& le)
			{return level.lock() == le.lock(); });
		if (iter != m_Levels.end())
		{
			level.lock()->Shutdown();
			m_Levels.erase(iter);
		}
	}

	LevelManager* LevelManager::s_Instance = nullptr;
}