#include "stdafx.h"
#include "PARS/Level/LevelManager.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailLayer.h"
#include "PARS/Input/Input.h"

//юс╫ц
#include "PARS/Layer/LayerManager.h"

namespace PARS
{
	LevelManager::LevelManager()
	{
		s_Instance = this;
	}

	void LevelManager::ProcessInput()
	{
		if (m_Level != nullptr && 
			(m_Level->GetLevelState() == LevelState::InGame || 
			m_Level->GetLevelState() == LevelState::Editor))
		{
			m_Level->ProcessInput();
		}
	}

	void LevelManager::Update(float deltaTime)
	{
		if (m_Level != nullptr)
		{
			m_IsUpdateLevel = true;
			if ((m_Level->GetLevelState() == LevelState::InGame ||
				m_Level->GetLevelState() == LevelState::Editor))
			{
				m_Level->Update(deltaTime);
			}
			m_IsUpdateLevel = false;
		}

		if (m_ReadyLevel != nullptr)
		{
			if (m_Level != nullptr)
			{
				m_Level->Shutdown();
				m_Level = nullptr;
			}

			m_Level = std::move(m_ReadyLevel);
			AddLevelToDetailLayer();
			m_Level->Initialize();

			m_ReadyLevel = nullptr;
		}
	}

	void LevelManager::Shutdown()
	{
		if (m_ReadyLevel != nullptr)
		{
			m_ReadyLevel->Shutdown();
			m_ReadyLevel = nullptr;
		}
		if (m_Level != nullptr)
		{
			m_Level->Shutdown();
			m_Level = nullptr;
		}
	}

	void LevelManager::OpenLevel(const SPtr<Level>& level)
	{
		m_ReadyLevel = level;
	}

	void LevelManager::ReadyOpenedLevel()
	{
		
	}

	void LevelManager::StartOpenedLevel()
	{
		if (m_Level != nullptr)
		{
			if (m_Level->GetLevelState() == LevelState::Editor)
			{
				m_Level->SetLevelState(LevelState::InGame);
				Input::SetCursorHide(true);
			}
		}
	}

	void LevelManager::StopOpenedLevel()
	{
		if (m_Level != nullptr)
		{
			if (m_Level->GetLevelState() == LevelState::InGame)
			{
				m_Level->SetLevelState(LevelState::Editor);
				Input::SetCursorHide(false);
			}
		}
	}

	void LevelManager::AddLevelToDetailLayer()
	{
		const auto& detailLayer = std::reinterpret_pointer_cast<LevelDetailLayer>(LayerManager::GetLayerManager()->GetLayerByName("Level Detail Layer"));
		if (detailLayer != nullptr)
		{
			detailLayer->AddSelectLevel(m_Level);
		}
	}

	LevelManager* LevelManager::s_Instance = nullptr;
}