#include "stdafx.h"
#include "PARS/Util/Content/Asset.h"
#include "PARS/Layer/EngineLayer/EditLayer/Core/EditLayer.h"
#include "PARS/Layer/LayerManager.h"

namespace PARS
{
	void Asset::OpenEditLayer(WPtr<class EditLayer>&& layer)
	{
		if (m_EditLayer.expired())
		{
			m_EditLayer = layer;
			LayerManager::GetLayerManager()->AddLayer(m_EditLayer.lock());
		}
	}
}