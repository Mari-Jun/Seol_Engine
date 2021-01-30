#pragma once

#include "PARS/Layer/Layer.h"

namespace PARS
{
	struct WindowInfo;
	class DirectX12;

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const WindowInfo& info, const WPtr<DirectX12>& directX12);
		~ImGuiLayer() = default;
		
		void Initialize() override;
		void Shutdown() override;
		void Update() override;
		void Draw();

	private:
		WindowInfo m_WindowInfo;
		WPtr<DirectX12> m_DirectX12;
	};
}


