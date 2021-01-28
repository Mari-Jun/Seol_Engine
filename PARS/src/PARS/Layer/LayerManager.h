#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Layer/Layer.h"

namespace PARS
{
	class LayerManager
	{
	public:
		LayerManager() = default;
		~LayerManager();

		void Update();

		void AddLayer(const SPtr<Layer>& layer);
		void RemoveLayer(const WPtr<Layer>& layer);

	private:
		std::vector<SPtr<Layer>> m_Layers;
	};
}


