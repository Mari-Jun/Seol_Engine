#include "stdafx.h"
#include "PARS/Layer/LayerManager.h"

namespace PARS
{
	void LayerManager::Update()
	{
		for (const auto& layer : m_Layers)
		{
			layer->Update();
		}

		std::vector<SPtr<Layer>> deadLayers;
		for (auto& layer : m_Layers)
		{
			if (layer->GetLayerState() == Layer::LayerState::Dead)
			{
				deadLayers.push_back(layer);
			}
		}

		for (auto& layer : deadLayers)
		{
			RemoveLayer(layer);
		}
	}

	void LayerManager::Shutdown()
	{
		for (auto layer : m_Layers)
		{
			if (layer != nullptr)
			{
				layer->Shutdown();
			}
		}
	}

	void LayerManager::AddLayer(const SPtr<Layer>& layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerManager::RemoveLayer(const WPtr<Layer>& layer)
	{
		auto iter = std::find_if(m_Layers.begin(), m_Layers.end(),
			[&layer](const WPtr<Layer>& ly)
			{return layer.lock() == ly.lock(); });
		if (iter != m_Layers.end())
		{
			layer.lock()->Shutdown();
			m_Layers.erase(iter);
		}
	}
}