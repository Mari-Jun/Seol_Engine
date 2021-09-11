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

	private:
		void StylePARS();

	private:
		SPtr<class DirectX12> m_DirectX12;

		ID3D12DescriptorHeap* m_SRVDescriptorHeap = nullptr;
		UINT m_SRVDescriptorSize = 0;
	};
}


