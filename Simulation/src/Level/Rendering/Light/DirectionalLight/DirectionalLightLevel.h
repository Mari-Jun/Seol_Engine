#pragma once

#include <PARS.h>
#include "DirectionalLightLayer.h"

namespace PARS
{
	class DirectionalLightLevel : public Level3D
	{
	public:
		DirectionalLightLevel();
		virtual ~DirectionalLightLevel() = default;

		void InitializeLevel() override;
		void UpdateLevel(float deltaTime) override;
	};
}


