#pragma once

#include "PARS/Core/Core.h"
#include "PARS/Math/Math.h"

namespace PARS
{
	struct WindowInfo;

	class DirectX12 : public std::enable_shared_from_this<DirectX12>
	{
	private:
		static SPtr<DirectX12> s_Instance;

	public:
		DirectX12();
		virtual ~DirectX12();

		bool Initailize();
		void ShutDown();

		bool ResizeWindow();

	private:
		bool CreateDevice();
		bool CreateCommandObjects();
		void CreateSwapChain();

		bool CreateHeaps();
		bool CreateRenderTargetViews();
		bool CreateDepthStecilView();
		
		void SetViewAndScissor();

	public:
		void WaitForGpuCompelete();
		void MoveToNextFrame();
	
	public:
		inline static  SPtr<DirectX12> GetDirectX12() { return s_Instance; }

		ID3D12Device* GetDevice() { return m_Device; }
		ID3D12CommandQueue* GetCommandQueue() { return m_CommandQueue; }
		ID3D12CommandAllocator* GetCommandAllocator() { return m_CommandAllocator; }
		ID3D12GraphicsCommandList* GetCommandList() { return m_CommandList; }
		ID3D12DescriptorHeap* GetCbvSrvUavHeap() { return m_CbvSrvUavDescriptorHeap; }

		ID3D12Resource* GetCurrentBackBuffer() const;
		D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const;
		D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;

		bool IsMass4xEnable() const { return m_Msaa4xEnable; }
		UINT GetMsaa4xQuality() const { return m_Msaa4xQuality; }

	public:
		void BeginScene(const Vec4& color);
		void EndScene();

	private:
		WindowInfo* m_WindowInfo = nullptr;

		IDXGIFactory4* m_Factory = nullptr;
		IDXGISwapChain3* m_SwapChain = nullptr;
		ID3D12Device* m_Device = nullptr;

		static constexpr UINT m_SwapChainBufferCount = 2;
		int m_CurrentSwapChainBuffer = 0;

		ID3D12Fence* m_Fence = nullptr;
		UINT64 m_FenceValue[m_SwapChainBufferCount] = { 0, };
		HANDLE m_FenceEvent = NULL;

		bool m_Msaa4xEnable = false;
		UINT m_Msaa4xQuality = 0;

		ID3D12CommandQueue* m_CommandQueue = nullptr;
		ID3D12CommandAllocator* m_CommandAllocator = nullptr;
		ID3D12GraphicsCommandList* m_CommandList = nullptr;

		ID3D12Resource* m_RenderTargetBuffers[m_SwapChainBufferCount] = { nullptr, };
		ID3D12DescriptorHeap* m_RtvDescriptorHeap = nullptr;
		UINT m_RtvDescriptorSize = 0;

		ID3D12Resource* m_DepthStencilBuffer = nullptr;
		ID3D12DescriptorHeap* m_DsvDescriptorHeap = nullptr;
		UINT m_DsvDescriptorSize = 0;

		ID3D12DescriptorHeap* m_CbvSrvUavDescriptorHeap = nullptr;
		UINT m_CbvSrvUavDescriptorSize = 0;

		D3D12_VIEWPORT m_Viewport;
		D3D12_RECT m_ScissorRect;
	};

}


