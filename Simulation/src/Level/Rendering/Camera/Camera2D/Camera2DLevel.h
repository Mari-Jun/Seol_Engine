#pragma once

#include <PARS.h>

namespace PARS
{
	class Camera2DLevel : public Level2D
	{
	public:
		Camera2DLevel();
		virtual ~Camera2DLevel() = default;

		void InitializeLevel() override;
		void UpdateLevel(float deltaTime) override;
	};
}



