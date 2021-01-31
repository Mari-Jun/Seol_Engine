#pragma once

#include "PARS/Actor/Actor.h"

namespace PARS
{
	class ActorManager final
	{
	public:
		ActorManager() = default;
		~ActorManager() = default;

		void ProcessInput();
		void Update(float deltaTime);
		void Shutdown();

		void AddActor(const SPtr<Actor>& actor);
		void RemoveActor(const WPtr<Actor>& actor);

	private:
		bool m_IsUpdateActors = false;
		std::vector<SPtr<Actor>> m_ReadyActors;
		std::vector<SPtr<Actor>> m_Actors;
	};
}


