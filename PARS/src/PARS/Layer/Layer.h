#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class Layer
	{
	public:
		enum class LayerState
		{
			Active, Hide, Dead
		};

		Layer(const std::string& name = "Defualt_Layer");
		virtual ~Layer() = default;

		virtual void Initialize() {}
		virtual void Shutdown() {}
		virtual void LayerInput() {}
		virtual void Update() {}
		virtual void ResizeLayer() {}

		void AddLevel(const SPtr<class Level>& level);

	protected:
		std::string m_LayerName;
		LayerState m_LayerState;

	public:
		const std::string& GetLayerName() const { return m_LayerName; }
		LayerState GetLayerState() const { return m_LayerState; }
		void SetLayerState(LayerState state) { m_LayerState = state; }

		void Destroy() { m_LayerState = LayerState::Dead; }
	};
}


