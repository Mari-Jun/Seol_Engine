#pragma once

#include <PARS.h>

namespace PARS
{
	class ClearColorLevel : public Level
	{
	public:
		ClearColorLevel();
		virtual ~ClearColorLevel();

		void InitializeLevel() override;
		void ShutdownLevel() override;
		void UpdateLevel(float deltaTime) override;
		
	};
}

