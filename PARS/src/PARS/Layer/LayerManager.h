#pragma once

#include "PARS/Layer/Layer.h"

namespace PARS
{
	class LayerManager
	{
	public:
		LayerManager() = default;
		~LayerManager() = default;

		void Update();
		void Shutdown();

		void AddLayer(const SPtr<Layer>& layer);
		void RemoveLayer(const WPtr<Layer>& layer);

	private:
		std::vector<SPtr<Layer>> m_Layers;
	};
}


