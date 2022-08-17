#pragma once

#include "PARS/Layer/Layer.h"
#include "PARS/Core/Window.h"

namespace PARS
{
	class ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer(const SPtr<class DirectX12>& directX);
		~ImGuiLayer() = default;
		
		void Initialize() override;
		void Shutdown() override;
		void Update() override;
		void Draw();

		void InitFromNewSRVHeap(ID3D12DescriptorHeap* srvHeap);

	private:
		void StylePARS();

	private:
		SPtr<class DirectX12> m_DirectX12;
	};
}


