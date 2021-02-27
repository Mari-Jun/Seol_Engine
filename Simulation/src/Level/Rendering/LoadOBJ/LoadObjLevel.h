#pragma once

#include <PARS.h>
#include "LoadObjLayer.h"

namespace PARS
{
	class LoadObjLevel : public Level3D
	{
	public:
		LoadObjLevel();
		virtual ~LoadObjLevel() = default;

		void InitializeLevel() override;
		void UpdateLevel(float deltaTime) override;
	};
}


