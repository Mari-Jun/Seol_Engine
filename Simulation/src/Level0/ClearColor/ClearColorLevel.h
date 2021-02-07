#pragma once

#include <PARS.h>

namespace PARS
{
	class ClearColorLevel : public Level
	{
	public:
		ClearColorLevel();
		virtual ~ClearColorLevel() = default;

		void InitializeLevel() override;
		void UpdateLevel(float deltaTime) override;

	};
}

