#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class ActorManager;

	class Level
	{
	public:
		enum class LevelState
		{
			Active, Paused, Dead
		};

		Level(const std::string& name = "Defualt_Level");
		virtual ~Level();

		virtual void InitializeLevel() {}
		virtual	void ShutdownLevel() {}
		void Initialize();		
		void Shutdown();
		virtual void LevelInput() {}
		void Update(float deltaTime);
		void UpdateActorManager(float deltaTime);
		virtual void UpdateLevel(float deltaTime) {};

		void AddActor(const SPtr<class Actor>& actor);
		void AddLayer(const SPtr<class Layer>& layer);

	protected:
		std::string m_LevelName;
		LevelState m_LevelState;

	private:
		UPtr<ActorManager> m_ActorManager;
		std::vector<WPtr<class Layer>> m_Layers;

	public:
		const std::string& GetLevelName() const { return m_LevelName; }
		LevelState GetLevelState() const { return m_LevelState; }
		void SetLevelState(LevelState state) { m_LevelState = state; }

		void SetLayerActive();
		void SetLayerHide();
		void Destroy() { m_LevelState = LevelState::Dead; }
	};
}


