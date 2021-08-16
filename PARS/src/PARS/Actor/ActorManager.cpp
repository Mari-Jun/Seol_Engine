#include "stdafx.h"
#include "PARS/Actor/ActorManager.h"
#include "PARS/Layer/LayerManager.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailLayer.h"

namespace PARS
{
	void ActorManager::ProcessInput()
	{
		for (const auto& actor : m_Actors)
		{
			if (actor->GetActorState() == Actor::ActorState::Active)
			{
				actor->ProcessInput();
			}
		}
	}

	void ActorManager::Update(float deltaTime)
	{
		m_IsUpdateActors = true;
		for (const auto& actor : m_Actors)
		{
			if (actor->GetActorState() == Actor::ActorState::Active)
			{
				actor->UpdateActor(deltaTime);
			}
		}
		m_IsUpdateActors = false;

		for (auto actor : m_ReadyActors)
		{
			actor->UpdateWorldMatrix();
			m_Actors.emplace_back(actor);
		}
		m_ReadyActors.clear();

		std::vector<SPtr<Actor>> deadActors;
		for (auto actor : m_Actors)
		{
			if (actor->GetActorState() == Actor::ActorState::Dead)
			{
				deadActors.emplace_back(actor);
			}
		}

		for (auto actor : deadActors)
		{
			RemoveActor(actor);
		}
	}

	void ActorManager::Shutdown()
	{
		for (auto actor : m_Actors)
		{
			if (actor != nullptr)
			{
				RemoveActorToDetailLayer(actor);
				actor->ShutdownActor();
			}
		}
	}

	void ActorManager::AddActor(const SPtr<Actor>& actor)
	{
		if (m_IsUpdateActors)
		{
			m_ReadyActors.emplace_back(actor);
		}
		else
		{
			m_Actors.emplace_back(actor);
		}
		actor->InitializeActor();

		AddActorToDetailLayer(actor);
	}

	void ActorManager::AddActorToDetailLayer(const SPtr<Actor>& actor)
	{
		std::string actorName = actor->GetActorName();
		++m_ActorCounts[actorName];
		actorName += " " + std::to_string(m_ActorCounts[actorName]);
		actor->SetActorName(actorName);

		const auto& detailLayer = std::reinterpret_pointer_cast<DetailLayer>(LayerManager::GetLayerManager()->GetLayerByName("Detail Layer"));
		if (detailLayer != nullptr)
		{
			detailLayer->AddActorToLayer(actor);
		}
	}

	void ActorManager::RemoveActor(const SPtr<Actor>& actor)
	{
		RemoveActorToDetailLayer(actor);

		auto iter = std::find_if(m_ReadyActors.begin(), m_ReadyActors.end(),
			[&actor](const SPtr<Actor>& ac)
			{return actor == ac; });
		if (iter != m_ReadyActors.end())
		{
			actor->ShutdownActor();
			m_ReadyActors.erase(iter);
		}

		iter = std::find_if(m_Actors.begin(), m_Actors.end(),
			[&actor](const SPtr<Actor>& ac)
			{return actor == ac; });
		if (iter != m_Actors.end())
		{
			actor->ShutdownActor();
			m_Actors.erase(iter);
		}
	}

	void ActorManager::RemoveActorToDetailLayer(const SPtr<Actor>& actor)
	{
		const auto& detailLayer = std::reinterpret_pointer_cast<DetailLayer>(LayerManager::GetLayerManager()->GetLayerByName("Detail Layer"));
		if (detailLayer != nullptr)
		{
			detailLayer->RemoveActorToLayer(actor->GetActorName());
		}
	}
}