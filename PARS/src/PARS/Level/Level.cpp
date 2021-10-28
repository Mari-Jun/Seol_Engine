#include "stdafx.h"
#include "PARS/Actor/ActorManager.h"
#include "PARS/Level/Level.h"
#include "PARS/Layer/LayerManager.h"
#include "PARS/Input/Input.h"

namespace PARS
{
	Level::Level(const std::string& name)
		: m_LevelName(name)
		, m_LevelState(LevelState::Editor)
	{
		m_DetailFunction = CreateUPtr<DetailFunction>();
		m_ActorManager = CreateUPtr<ActorManager>();
		m_EditorInputFactory = CreateUPtr<InputFactory>();
		m_InGameInputFactory = CreateUPtr<InputFactory>();
	}

	Level::~Level()
	{
	}

	void Level::Initialize()
	{
		InitializeLevel();
		m_DetailFunction->Initailize(GetLevelName());
		PARS_INFO("\nOpen " + GetLevelName() + "\n");
	}

	void Level::Shutdown()
	{
		ShutdownLevel();
		m_ActorManager->Shutdown();
	}

	void Level::ProcessInput()
	{
		LevelInput();

		switch (m_LevelState)
		{
		case PARS::LevelState::InGame:
			m_InGameInputFactory->ProcessInput();
			m_ActorManager->ProcessInput();
			break;
		case PARS::LevelState::Editor:
			m_EditorInputFactory->ProcessInput();
			break;
		default:
			break;
		}
	}

	void Level::Update(float deltaTime)
	{
		UpdateActorManager(deltaTime);
		UpdateLevel(deltaTime);
	}

	void Level::UpdateActorManager(float deltaTime)
	{
		switch (m_LevelState)
		{
		case PARS::LevelState::InGame:
			m_ActorManager->UpdateInGame(deltaTime);
			break;
		case PARS::LevelState::Editor:
			m_ActorManager->UpdateEditor(deltaTime);
			break;
		default:
			break;
		}
	}

	void Level::AddActor(const SPtr<Actor>& actor)
	{
		m_ActorManager->AddActor(actor);
	}

	void Level::RemoveActor(const SPtr<class Actor>& actor)
	{
		m_ActorManager->RemoveActor(actor);
	}

	void Level::AddOnceAction(std::string&& name, int key, const std::function<void()>& func, bool isEditor)
	{
		if (isEditor)
		{
			m_EditorInputFactory->AddOnceAction(std::move(name), key, func);
		}
		else
		{
			m_InGameInputFactory->AddOnceAction(std::move(name), key, func);
		}
	}

	void Level::AddLoopAction(std::string&& name, int key, const std::function<void()>& func, bool isEditor)
	{
		if (isEditor)
		{
			m_EditorInputFactory->AddLoopAction(std::move(name), key, func);
		}
		else
		{
			m_InGameInputFactory->AddLoopAction(std::move(name), key, func);
		}
	}

	void Level::AddAxisAction(std::string&& name, std::vector<KeyAxis>&& keyAndAxis, const std::function<void(float)>& func, bool isEditor)
	{
		if (isEditor)
		{
			m_EditorInputFactory->AddAxisAction(std::move(name), std::move(keyAndAxis), func);
		}
		else
		{
			m_InGameInputFactory->AddAxisAction(std::move(name), std::move(keyAndAxis), func);
		}
	}

	void Level::AddReleaseAction(std::string&& name, int key, const std::function<void()>& func, bool isEditor)
	{
		if (isEditor)
		{
			m_EditorInputFactory->AddReleaseAction(std::move(name), key, func);
		}
		else
		{
			m_InGameInputFactory->AddReleaseAction(std::move(name), key, func);
		}
	}

	void Level::ActiveAction(ActionType type, std::string&& name, bool active, bool isEditor)
	{
		if (isEditor)
		{
			m_EditorInputFactory->ActiceAction(type, std::move(name), active);
		}
		else
		{
			m_InGameInputFactory->ActiceAction(type, std::move(name), active);
		}
	}

	void Level::AddLayer(const SPtr<Layer>& layer)
	{
		auto layerManger = LayerManager::GetLayerManager();
		layerManger->AddLayer(layer);
		m_Layers.emplace_back(layer);
	}

	void Level::AddLevelSettingFunctionInfo(FunctionInfo&& info)
	{
		m_DetailFunction->AddFunctionInfo(std::move(info));
	}

	void Level::OnUpdateDetailInfo(std::function<void(const DetailInfo& info)> function)
	{
		function(m_DetailFunction->GetDetailInfo());
	}

	void Level::SetLayerActive()
	{
		for (const auto& layer : m_Layers)
		{
			layer.lock()->SetLayerState(Layer::LayerState::Active);
		}
	}

	void Level::SetLayerHide()
	{
		for (const auto& layer : m_Layers)
		{
			layer.lock()->SetLayerState(Layer::LayerState::Hide);
		}
	}
}
