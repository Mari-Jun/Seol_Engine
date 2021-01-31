#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class Level
	{
	public:
		enum class LevelState
		{
			Active, Paused, Dead
		};

		Level(const std::string& name = "Defualt_Level");
		virtual ~Level();

		virtual void Initialize() {}
		virtual void Shutdown() {}
		virtual void Update() {}

		const std::string& GetLevelName() const { return m_LevelName; }
		LevelState GetLevelState() const { return m_LevelState; }

		void SetStateDead() { m_LevelState = LevelState::Dead; }
		bool IsDeadLayer() { return m_LevelState == LevelState::Dead; }

	protected:
		std::string m_LevelName;
		LevelState m_LevelState;
	};
}


