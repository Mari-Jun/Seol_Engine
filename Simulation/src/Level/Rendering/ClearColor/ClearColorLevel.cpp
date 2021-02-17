#include "ClearColorLevel.h"
#include "ClearColorLayer.h"

namespace PARS
{
	ClearColorLevel::ClearColorLevel()
		: Level("Clear Color")
	{
	}

	ClearColorLevel::~ClearColorLevel()
	{
	}

	void ClearColorLevel::InitializeLevel()
	{
		auto layer = PARS::CreateSPtr<PARS::ClearColorLayer>();
		layer->OnDestroy([this]() {DestroyLevel(); });
		AddLayer(layer);	
	}

	void ClearColorLevel::UpdateLevel(float deltaTime)
	{
	
	}

	void ClearColorLevel::DestroyLevel()
	{
		SetLevelState(LevelState::Dead);
	}
}
