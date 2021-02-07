#include "ClearColorLevel.h"
#include "ClearColorLayer.h"

namespace PARS
{
	ClearColorLevel::ClearColorLevel()
		: Level("Clear Color Level")
	{
	}

	void ClearColorLevel::InitializeLevel()
	{
		AddLayer(PARS::CreateSPtr<PARS::ClearColorLayer>());
	}

	void ClearColorLevel::UpdateLevel(float deltaTime)
	{
	
	}
}
