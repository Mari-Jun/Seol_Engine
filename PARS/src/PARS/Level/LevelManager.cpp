#include "stdafx.h"
#include "PARS/Level/LevelManager.h"

//�ӽ�
#include "PARS/Layer/LayerManager.h"

namespace PARS
{
	LevelManager::LevelManager()
	{
		s_Instance = this;
	}

	void LevelManager::ProcessInput()
	{
		if (m_Level != nullptr && m_Level->GetLevelState() == Level::LevelState::Active)
		{
			m_Level->LevelInput();
		}
	}

	void LevelManager::Update(float deltaTime)
	{
		if (m_Level != nullptr)
		{
			m_IsUpdateLevel = true;
			if (m_Level->GetLevelState() == Level::LevelState::Active)
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

		//�ӽ÷� EditorLayer, ContentLayer�� ������
		//���߿� ViewportLayer�� ����� �׶� �ٽ� �����ϴ°ɷ�.

		const auto& editorLayer = LayerManager::GetLayerManager()->GetLayerByName("Editor Layer");
		if (editorLayer != nullptr)
		{
			editorLayer->SetLayerState(Layer::LayerState::Hide);
		}
	}

	LevelManager* LevelManager::s_Instance = nullptr;
}