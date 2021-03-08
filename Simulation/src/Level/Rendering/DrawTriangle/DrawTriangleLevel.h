#pragma once

#include <PARS.h>
#include "DrawTriangleLayer.h"

namespace PARS
{
	class DrawTriangleLevel : public Level2D
	{
	public:
		DrawTriangleLevel();
		virtual ~DrawTriangleLevel() = default;

		void InitializeLevel() override;
		void UpdateLevel(float deltaTime) override;
	};
}


