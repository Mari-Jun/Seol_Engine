#pragma once

#include "PARS/Level/Level.h"

namespace PARS
{
	class LevelManager final
	{
	public:
		LevelManager();
		~LevelManager() = default;

		void ProcessInput();
		void Update(float deltaTime);
		void Shutdown();

		void OpenLevel(const SPtr<Level>& level);
		void ReadyOpenedLevel();
		void StartOpenedLevel();
		void StopOpenedLevel();

		const SPtr<Level>& GetOpenedLevel() const { return m_Level; }
		inline static LevelManager* GetLevelManager() { return s_Instance; }

	private:
		void AddLevelToDetailLayer();

	private:
		bool m_IsUpdateLevel = false;
		SPtr<Level> m_Level = nullptr;
		SPtr<Level> m_ReadyLevel = nullptr;
		static LevelManager* s_Instance;
	};
}


