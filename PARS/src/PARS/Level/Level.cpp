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
		
	}

	Level::~Level()
	{
	}

	void Level::Initialize()
	{
		m_ActorManager = CreateUPtr<ActorManager>();
		InitializeLevel();
	}

	void Level::Shutdown()
	{
		ShutdownLevel();
		m_ActorManager->Shutdown();
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

	void Level::AddLayer(const SPtr<Layer>& layer)
	{
		auto layerManger = LayerManager::GetLayerManager();
		layerManger->AddLayer(layer);
		m_Layers.emplace_back(layer);
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
