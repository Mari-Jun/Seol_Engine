#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class Layer
	{
	public:
		enum class LayerState
		{
			Active, Dead
		};

		Layer(const std::string& name = "Defualt_Layer");
		virtual ~Layer();

		virtual void Initialize() {}
		virtual void Shutdown() {}
		virtual void Update() {}

		const std::string& GetLayerName() const { return m_LayerName; }
		LayerState GetLayerState() const { return m_LayerState; }

		void SetStateDead() { m_LayerState = LayerState::Dead; }

	protected:
		std::string m_LayerName;
		LayerState m_LayerState;
	};
}


