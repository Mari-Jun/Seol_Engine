#pragma once

#include <PARS.h>
#include "DrawTriangleLayer.h"
#include "PARS/Component/Render/MeshComponent.h"

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


