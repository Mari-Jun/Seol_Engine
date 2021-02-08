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
		if (!m_Levels.empty())
		{
			const auto& level = m_Levels.top();
			if (level->GetLevelState() == Level::LevelState::Active)
			{
				level->LevelInput();
			}
		}
	}

	void LevelManager::Update(float deltaTime)
	{
		if (!m_Levels.empty())
		{
			m_IsUpdateLevels = true;
			const auto& level = m_Levels.top();
			if (level->GetLevelState() == Level::LevelState::Active)
			{
				level->Update(deltaTime);
			}
			m_IsUpdateLevels = false;

			if (m_ReadyLevels != nullptr)
			{
				level->SetLayerHide();
				m_Levels.emplace(m_ReadyLevels);
				m_ReadyLevels = nullptr;
			}

			std::vector<SPtr<Level>> deadLevels;
			if (level->GetLevelState() == Level::LevelState::Dead)
			{
				deadLevels.emplace_back(level);
			}

			for (auto level : deadLevels)
			{
				RemoveLevel(level);
			}
		}
	}

	void LevelManager::Shutdown()
	{
		while (!m_Levels.empty())
		{
			auto level = m_Levels.top();
			if (level != nullptr)
			{
				level->Shutdown();
			}
			m_Levels.pop();
		}
	}

	void LevelManager::AddLevel(const SPtr<Level>& level)
	{
		if (m_IsUpdateLevels)
		{
			m_ReadyLevels = level;
		}
		else
		{
			if (!m_Levels.empty())
			{
				const auto& level = m_Levels.top();
				level->SetLayerHide();
			}
			m_Levels.emplace(level);
		}
		level->Initialize();
	}

	void LevelManager::RemoveLevel(const WPtr<Level>& level)
	{
		if (m_ReadyLevels != nullptr && level.lock() == m_ReadyLevels)
		{
			m_ReadyLevels->Shutdown();
		}

		if (!m_Levels.empty() && level.lock() == m_Levels.top())
		{
			m_Levels.top()->Shutdown();
			m_Levels.pop();
			if (!m_Levels.empty())
			{
				m_Levels.top()->SetLayerActive();
			}
		}
	}

	LevelManager* LevelManager::s_Instance = nullptr;
}