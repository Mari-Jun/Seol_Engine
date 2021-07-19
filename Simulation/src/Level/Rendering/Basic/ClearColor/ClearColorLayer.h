#pragma once

#include <PARS.h>
#include "Level/Core/BasicLayer.h"	

namespace PARS
{
	class ClearColorLayer : public BasicLayer
	{
	public:
		ClearColorLayer();
		virtual ~ClearColorLayer() = default;

		void UpdateDetail() override;
	};
}



