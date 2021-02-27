#pragma once
#include <PARS.h>
#include "Level/Core/BasicLayer.h"  

namespace PARS
{
	class LoadObjLayer : public BasicLayer
	{
	public:
		LoadObjLayer();
		virtual ~LoadObjLayer() = default;

		void Initialize() override;
	};
}


