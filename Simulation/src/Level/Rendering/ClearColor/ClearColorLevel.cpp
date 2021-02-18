#include "ClearColorLevel.h"
#include "ClearColorLayer.h"
#include "PARS/Component/Render/MeshComponent.h"

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
		layer->OnDestroy([this]() {Destroy(); });
		AddLayer(layer);	
	}

	void ClearColorLevel::UpdateLevel(float deltaTime)
	{
	
	}
}
