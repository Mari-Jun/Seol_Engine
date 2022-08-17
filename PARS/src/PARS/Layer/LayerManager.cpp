#include "stdafx.h"
#include "PARS/Layer/LayerManager.h"

namespace PARS
{
	LayerManager::LayerManager()
	{
		s_Instance = this;
	}

	void LayerManager::ProcessInput()
	{
		for (const auto& layer : m_Layers)
		{
			if (layer != nullptr && layer->GetLayerState() == Layer::LayerState::Active)
			{
				layer->LayerInput();
			}
		}
	}

	void LayerManager::Update()
	{
		m_IsUpdateLayers = true;
		for (const auto& layer : m_Layers)
		{
			if (layer->GetLayerState() == Layer::LayerState::Active)
			{
				layer->Update();
			}
		}
		m_IsUpdateLayers = false;

		for (auto layer : m_ReadyLayers)
		{
			m_Layers.emplace_back(layer);
		}
		m_ReadyLayers.clear();

		std::vector<SPtr<Layer>> deadLayers;
		for (auto layer : m_Layers)
		{
			if (layer->GetLayerState() == Layer::LayerState::Dead)
			{
				deadLayers.push_back(layer);
			}
		}

		for (auto layer : deadLayers)
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
		m_Layers.clear();
	}

	void LayerManager::ResizeLayer()
	{
		for (const auto& layer : m_Layers)
		{
			layer->ResizeLayer();
		}
	}

	void LayerManager::AddLayer(const SPtr<Layer>& layer)
	{
		if (m_IsUpdateLayers)
		{
			m_ReadyLayers.emplace_back(layer);
		}
		else
		{
			m_Layers.emplace_back(layer);
		}
		layer->Initialize();
	}

	void LayerManager::RemoveLayer(const WPtr<Layer>& layer)
	{
		auto iter = std::find_if(m_ReadyLayers.begin(), m_ReadyLayers.end(),
			[&layer](const WPtr<Layer>& ly)
			{return layer.lock() == ly.lock(); });
		if (iter != m_ReadyLayers.end())
		{
			layer.lock()->Shutdown();
			m_ReadyLayers.erase(iter);
		}

		iter = std::find_if(m_Layers.begin(), m_Layers.end(),
			[&layer](const WPtr<Layer>& ly)
			{return layer.lock() == ly.lock(); });
		if (iter != m_Layers.end())
		{
			layer.lock()->Shutdown();
			m_Layers.erase(iter);
		}
	}

	const SPtr<Layer>& LayerManager::GetLayerByName(const std::string& name)
	{
		auto iter = std::find_if(m_ReadyLayers.cbegin(), m_ReadyLayers.cend(),
			[&name](const SPtr<Layer>& layer)
			{return layer->GetLayerName() == name; });
		if (iter != m_ReadyLayers.cend())
			return *iter;

		iter = std::find_if(m_Layers.cbegin(), m_Layers.cend(),
			[&name](const SPtr<Layer>& layer)
			{return layer->GetLayerName() == name; });
		if (iter != m_Layers.cend())
			return *iter;

		return nullptr;
	}

	LayerManager* LayerManager::s_Instance = nullptr;
}