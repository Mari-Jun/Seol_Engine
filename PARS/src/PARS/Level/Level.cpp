#include "stdafx.h"
#include "PARS/Actor/ActorManager.h"
#include "PARS/Level/Level.h"
#include "PARS/Layer/LayerManager.h"

namespace PARS
{
	Level::Level(const std::string& name)
		: m_LevelName(name)
		, m_LevelState(LevelState::Active)
	{
		m_DetailFunction = CreateUPtr<DetailFunction>();
	}

	Level::~Level()
	{
	}

	void Level::Initialize()
	{
		m_ActorManager = CreateUPtr<ActorManager>();
		InitializeLevel();
		m_DetailFunction->Initailize(GetLevelName());
		PARS_INFO("\nOpen " + GetLevelName() + "\n");
	}

	void Level::Shutdown()
	{
		ShutdownLevel();
		m_ActorManager->Shutdown();
	}

	void Level::LevelInput()
	{
		m_ActorManager->ProcessInput();
	}

	void Level::Update(float deltaTime)
	{
		UpdateActorManager(deltaTime);
		UpdateLevel(deltaTime);
	}

	void Level::UpdateActorManager(float deltaTime)
	{
		m_ActorManager->Update(deltaTime);
	}

	void Level::AddActor(const SPtr<Actor>& actor)
	{
		m_ActorManager->AddActor(actor);
	}

	void Level::RemoveActor(const SPtr<class Actor>& actor)
	{
		m_ActorManager->RemoveActor(actor);
	}
	void Level::AddOnceAction(std::string&& name, int key, const std::function<void()>& func)
	{
		m_InputFactory->AddOnceAction(std::move(name), key, func);
	}

	void Level::AddLoopAction(std::string&& name, int key, const std::function<void()>& func)
	{
		m_InputFactory->AddLoopAction(std::move(name), key, func);
	}

	void Level::AddAxisAction(std::string&& name, std::vector<KeyAxis>&& keyAndAxis, const std::function<void(float)>& func)
	{
		m_InputFactory->AddAxisAction(std::move(name), std::move(keyAndAxis), func);
	}

	void Level::ActiveAction(ActionType type, std::string&& name, bool active)
	{
		m_InputFactory->ActiceAction(type, std::move(name), active);
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
