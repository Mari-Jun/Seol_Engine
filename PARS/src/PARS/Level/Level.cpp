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
	}

	void Level::Shutdown()
	{
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

	void Level::AddActor(const SPtr<class Actor>& actor)
	{
		m_ActorManager->AddActor(actor);
		actor->Initialize();
	}

	void Level::AddLayer(const SPtr<class Layer>& layer)
	{
		auto layerManger = LayerManager::GetLayerManager();
		layerManger.AddLayer(layer);
	}
}
