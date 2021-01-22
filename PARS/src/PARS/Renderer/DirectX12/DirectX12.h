#pragma once

namespace PARS
{
	struct WindowInfo;

	class DirectX12
	{
	public:
		DirectX12(const WindowInfo& info);
		virtual ~DirectX12();

		bool Initailize();
		void ShutDown();

	private:
		bool CreateDevice();
		bool CreateCommandObjects();
		void CreateSwapChain();

		bool CreateRtvDsvHeap();
		bool CreateRenderTargetViews();
		void CreateDepthStecilView();
		
		void SetViewAndScissor();

		void WaitForGpuCompelete();

	public:
		void BeginScene(const XMFLOAT4& color = { 0.0f, 0.0f, 0.0f, 1.0f });
		void EndScene();

	private:
		WindowInfo m_WindowInfo;

		IDXGIFactory4* m_Factory = nullptr;
		IDXGISwapChain3* m_SwapChain = nullptr;
		ID3D12Device* m_Device = nullptr;

		ID3D12Fence* m_Fence = nullptr;
		UINT64 m_FenceValue = 0;
		HANDLE m_FenceEvent = NULL;

		bool m_Msaa4xEnable = false;
		UINT m_Msaa4xQuality = 0;

		ID3D12CommandQueue* m_CommandQueue = nullptr;
		ID3D12CommandAllocator* m_CommandAllocator = nullptr;
		ID3D12GraphicsCommandList* m_CommandList = nullptr;

		static constexpr int m_SwapChainBufferCount = 2;
		int m_CurrentSwapChainBuffer = 0;

		ID3D12Resource* m_RenderTargetBuffers[m_SwapChainBufferCount] = { nullptr, };
		ID3D12DescriptorHeap* m_RtvDescriptorHeap = nullptr;
		UINT m_RtvDescriptorSize = 0;

		ID3D12Resource* m_DepthStencilBuffer = nullptr;
		ID3D12DescriptorHeap* m_DsvDescriptorHeap = nullptr;
		UINT m_DsvDescriptorSize = 0;

		D3D12_VIEWPORT m_Viewport;
		D3D12_RECT m_ScissorRect;

	};
}


