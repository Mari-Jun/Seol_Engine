#pragma once

#include "PARS/Layer/Layer.h"

namespace PARS
{
	class LayerManager
	{
	public:
		LayerManager();
		~LayerManager() = default;

		void Update();
		void Shutdown();
		void ResizeLayer();

		void AddLayer(const SPtr<Layer>& layer);
		void RemoveLayer(const WPtr<Layer>& layer);

		const SPtr<Layer>& GetLayerByName(const std::string& name);

		inline static LayerManager* GetLayerManager() { return s_Instance; }

	private:
		bool m_IsUpdateLayers = false;
		std::vector<SPtr<Layer>> m_ReadyLayers;
		std::vector<SPtr<Layer>> m_Layers;
		static LayerManager* s_Instance;
	};
}


