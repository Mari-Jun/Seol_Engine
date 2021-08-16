#include "stdafx.h"
#include "PARS/Level/LevelManager.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailLayer.h"

//임시
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

		//임시로 EditorLayer, ContentLayer, ViewportLayer는 숨기자
		//나중에 ViewportLayer가 완성되면 그때 다시 수정하는걸로.

		const auto& Editorlayer = LayerManager::GetLayerManager()->GetLayerByName("Editor Layer");
		if (Editorlayer != nullptr)
		{
			Editorlayer->SetLayerState(Layer::LayerState::Hide);
		}
		const auto& Contentlayer = LayerManager::GetLayerManager()->GetLayerByName("Content Layer");
		if (Contentlayer != nullptr)
		{
			Contentlayer->SetLayerState(Layer::LayerState::Hide);
		}
		const auto& Viewportlayer = LayerManager::GetLayerManager()->GetLayerByName("Viewport Layer");
		if (Viewportlayer != nullptr)
		{
			Viewportlayer->SetLayerState(Layer::LayerState::Hide);
		}
	}

	void LevelManager::AddLevelToDetailLayer()
	{
		const auto& detailLayer = std::reinterpret_pointer_cast<DetailLayer>(LayerManager::GetLayerManager()->GetLayerByName("Detail Layer"));
		if (detailLayer != nullptr)
		{
			detailLayer->SetLevelToLayer(m_Level);
		}
	}

	LevelManager* LevelManager::s_Instance = nullptr;
}