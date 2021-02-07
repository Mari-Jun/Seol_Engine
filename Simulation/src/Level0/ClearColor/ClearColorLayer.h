#pragma once

#include <PARS.h>

namespace PARS
{
	class ClearColorLayer : public Layer
	{
	public:
		ClearColorLayer();
		virtual ~ClearColorLayer() = default;

		void Update() override;
	};
}



