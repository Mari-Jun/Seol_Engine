#pragma once

#include <PARS.h>
#include "Level/Core/BasicLayer.h"	

namespace PARS
{
	class DrawTriangleLayer : public BasicLayer
	{
	public:
		DrawTriangleLayer();
		virtual ~DrawTriangleLayer() = default;

		void UpdateGUI() override;
	};
}


