#pragma once

#include <PARS.h>
#include "Level/Core/BasicLayer.h"

namespace PARS
{
	class Camera2DLayer : public BasicLayer
	{
	public:
		Camera2DLayer();
		virtual ~Camera2DLayer() = default;

		void Initialize() override;
		void UpdateGUI() override;
	};
}



