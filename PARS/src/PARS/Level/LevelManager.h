#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Level/Level.h"

namespace PARS
{
	class LevelManager
	{
	public:
		LevelManager() = default;
		~LevelManager() = default;

		void Update();
		void Shutdown();

		void AddLevel(const SPtr<Level>& Level);
		void RemoveLevel(const WPtr<Level>& Level);

	private:
		std::vector<SPtr<Level>> m_Levels;
	};
}


