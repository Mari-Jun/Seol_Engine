#pragma once

#include "PARS/Layer/Layer.h"
#include "PARS/Core/Window.h"

namespace PARS
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;
		
		void Initialize() override;
		void Shutdown() override;
		void Update() override;
		void Draw();
	};
}


