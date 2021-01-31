#pragma once

#include "PARS/Layer/Layer.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"

namespace PARS
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const WindowInfo& info);
		~ImGuiLayer() = default;
		
		void Initialize() override;
		void Shutdown() override;
		void Update() override;
		void Draw();

	private:
		WindowInfo m_WindowInfo;
	};
}


