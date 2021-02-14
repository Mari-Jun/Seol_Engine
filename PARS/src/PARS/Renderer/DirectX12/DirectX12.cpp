#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"

namespace PARS
{
	DirectX12::DirectX12()
	{
		
	}

	DirectX12::~DirectX12()
	{
	}
	
	bool DirectX12::Initailize()
	{
		m_WindowInfo = Window::GetWindowInfo();

		bool result = CreateDevice();
		if (!result) return false;

		result = CreateCommandObjects();
		if (!result) return false;

		CreateSwapChain();

		result = CreateHeaps();
		if (!result) return false;

		result = ResizeWindow();
		if (!result) return false;
		
		s_Instance = this;

		return true;
	}

	void DirectX12::ShutDown()
	{
		WaitForGpuCompelete();

		CloseHandle(m_FenceEvent);

		if(m_DepthStencilBuffer!=nullptr) m_DepthStencilBuffer->Release();
		if (m_DsvDescriptorHeap != nullptr) m_DsvDescriptorHeap->Release();
		for (auto rtvBuffer : m_RenderTargetBuffers)
		{
			if (rtvBuffer != nullptr) rtvBuffer->Release();
		}
		if (m_RtvDescriptorHeap != nullptr) m_RtvDescriptorHeap->Release();
		if (m_CbvSrvUavDescriptorHeap != nullptr) m_CbvSrvUavDescriptorHeap->Release();
		if (m_SwapChain != nullptr) m_SwapChain->Release();
		if (m_CommandList != nullptr) m_CommandList->Release();
		if (m_CommandAllocator != nullptr) m_CommandAllocator->Release();
		if (m_CommandQueue != nullptr) m_CommandQueue->Release();
		if (m_Fence != nullptr) m_Fence->Release();
		if (m_Device != nullptr) m_Device->Release();
		if (m_Factory != nullptr) m_Factory->Release();

#if defined(_DEBUG)
		IDXGIDebug1* giDebug = nullptr;
		DXGIGetDebugInterface1(0, IID_PPV_ARGS(&giDebug));
		HRESULT result = giDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_DETAIL);
		giDebug->Release();
#endif

	}

	bool DirectX12::ResizeWindow()
	{
		m_WindowInfo = Window::GetWindowInfo();

		WaitForGpuCompelete();

		HRESULT hResult = m_CommandList->Reset(m_CommandAllocator, nullptr);
		if (FAILED(hResult)) return false;

		for (UINT i = 0; i < m_SwapChainBufferCount; ++i)
		{
			if(m_RenderTargetBuffers[i]!=nullptr) m_RenderTargetBuffers[i]->Release();
		}
		if (m_DepthStencilBuffer != nullptr) m_DepthStencilBuffer->Release();

		hResult = m_SwapChain->ResizeBuffers(m_SwapChainBufferCount, m_WindowInfo->m_Width, m_WindowInfo->m_Height,
			DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		if (FAILED(hResult)) return false;

		m_CurrentSwapChainBuffer = 0;

		bool result = CreateRenderTargetViews();
		if (!result) return false;

		result = CreateDepthStecilView();
		if (!result) return false;

		D3D12_RESOURCE_BARRIER resourceBarrier;
		resourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		resourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		resourceBarrier.Transition.pResource = m_DepthStencilBuffer;
		resourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
		resourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
		resourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		m_CommandList->ResourceBarrier(1, &resourceBarrier);

		//Done recording commands
		hResult = m_CommandList->Close();
		if (FAILED(hResult)) return false;

		//Add the command list to queue for excution
		ID3D12CommandList* commandLists[] = { m_CommandList };
		m_CommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

		WaitForGpuCompelete();

		SetViewAndScissor();

		return true;
	}

	bool DirectX12::CreateDevice()
	{
		HRESULT result;
		UINT factoryFlags = 0;


#if defined(_DEBUG)
		//Enable D3D12 debug layer.
		{
			ID3D12Debug* debugController;
			result = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
			if (FAILED(result)) return false;
			debugController->EnableDebugLayer();
			debugController->Release();
			factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
#endif

		//Create Factory
		result = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&m_Factory));
		if (FAILED(result)) return false;

		//Try to create hardware device
		IDXGIAdapter1* adapter = nullptr;
		for (UINT i = 0; DXGI_ERROR_NOT_FOUND != m_Factory->EnumAdapters1(i, &adapter); ++i)
		{
			DXGI_ADAPTER_DESC1 adapterDesc;
			adapter->GetDesc1(&adapterDesc);
			if (adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
			if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_Device)))) break;
		}

		//if you cannot create a device level 12.0, create a WARP device 
		if (adapter == nullptr)
		{
			m_Factory->EnumWarpAdapter(IID_PPV_ARGS(&adapter));
			D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device));
		}

		//create an event handle to use for frame synchronization
		result = m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence));
		for (int i = 0; i < m_SwapChainBufferCount; ++i)
		{
			m_FenceValue[i] = 0;
		}
		m_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

		//check 4X MSAA
		D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msaaQualityLevels;
		msaaQualityLevels.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		msaaQualityLevels.SampleCount = 4;
		msaaQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
		msaaQualityLevels.NumQualityLevels = 0;
		m_Device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &msaaQualityLevels, sizeof(msaaQualityLevels));
		m_Msaa4xQuality = msaaQualityLevels.NumQualityLevels;
		m_Msaa4xEnable = (m_Msaa4xQuality > 1) ? true : false;

		if (adapter != nullptr)
		{
			adapter->Release();
		}

		return true;
	}

	bool DirectX12::CreateCommandObjects()
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc;
		ZeroMemory(&queueDesc, sizeof(queueDesc));
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		HRESULT result = m_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_CommandQueue));
		if (FAILED(result)) return false;

		result = m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_CommandAllocator));
		if (FAILED(result)) return false;

		result = m_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CommandAllocator, nullptr, IID_PPV_ARGS(&m_CommandList));
		if (FAILED(result)) return false;

		m_CommandList->Close();

		return true;
	}

	void DirectX12::CreateSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC scDesc;
		ZeroMemory(&scDesc, sizeof(scDesc));
		scDesc.BufferDesc.Width = m_WindowInfo->m_Width;
		scDesc.BufferDesc.Height = m_WindowInfo->m_Height;
		scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scDesc.BufferDesc.RefreshRate.Numerator = 60;
		scDesc.BufferDesc.RefreshRate.Denominator = 1;
		scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scDesc.SampleDesc.Count = m_Msaa4xEnable ? 4 : 1;
		scDesc.SampleDesc.Quality = m_Msaa4xEnable ? m_Msaa4xQuality - 1 : 0;
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDesc.BufferCount = m_SwapChainBufferCount;
		scDesc.OutputWindow = m_WindowInfo->m_hwnd;
		scDesc.Windowed = TRUE;
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		m_Factory->CreateSwapChain(m_CommandQueue, &scDesc,	(IDXGISwapChain**)(&m_SwapChain));

		m_CurrentSwapChainBuffer = m_SwapChain->GetCurrentBackBufferIndex();

		m_Factory->MakeWindowAssociation(m_WindowInfo->m_hwnd, DXGI_MWA_NO_ALT_ENTER);
	}

	bool DirectX12::CreateHeaps()
	{
		D3D12_DESCRIPTOR_HEAP_DESC rtvDHDesc;
		ZeroMemory(&rtvDHDesc, sizeof(rtvDHDesc));
		rtvDHDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvDHDesc.NumDescriptors = m_SwapChainBufferCount;
		rtvDHDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		rtvDHDesc.NodeMask = 0;
		HRESULT result = m_Device->CreateDescriptorHeap(&rtvDHDesc, IID_PPV_ARGS(&m_RtvDescriptorHeap));
		if (FAILED(result)) return false;
		m_RtvDescriptorSize = m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		D3D12_DESCRIPTOR_HEAP_DESC dsvDHDesc;
		ZeroMemory(&dsvDHDesc, sizeof(dsvDHDesc));
		dsvDHDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsvDHDesc.NumDescriptors = 1;
		dsvDHDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		dsvDHDesc.NodeMask = 0;
		result = m_Device->CreateDescriptorHeap(&dsvDHDesc, IID_PPV_ARGS(&m_DsvDescriptorHeap));
		if (FAILED(result)) return false;
		m_DsvDescriptorSize = m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

		D3D12_DESCRIPTOR_HEAP_DESC csuDHDesc;
		ZeroMemory(&csuDHDesc, sizeof(csuDHDesc));
		csuDHDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		csuDHDesc.NumDescriptors = 1;
		csuDHDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		csuDHDesc.NodeMask = 0;
		result = m_Device->CreateDescriptorHeap(&csuDHDesc, IID_PPV_ARGS(&m_CbvSrvUavDescriptorHeap));
		if (FAILED(result)) return false;
		m_CbvSrvUavDescriptorSize = m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		return true;
	}

	bool DirectX12::CreateRenderTargetViews()
	{
		HRESULT result;
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		for (UINT i = 0; i < m_SwapChainBufferCount; ++i)
		{
			result = m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&m_RenderTargetBuffers[i]));
			if (FAILED(result)) return false;
			m_Device->CreateRenderTargetView(m_RenderTargetBuffers[i], nullptr, rtvHandle);
			rtvHandle.ptr += m_RtvDescriptorSize;
		}
		return true;
	}

	bool DirectX12::CreateDepthStecilView()
	{
		D3D12_RESOURCE_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(dsvDesc));
		dsvDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		dsvDesc.Alignment = 0;
		dsvDesc.Width = m_WindowInfo->m_Width;
		dsvDesc.Height = m_WindowInfo->m_Height;
		dsvDesc.DepthOrArraySize = 1;
		dsvDesc.MipLevels = 1;
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.SampleDesc.Count = m_Msaa4xEnable ? 4 : 1;
		dsvDesc.SampleDesc.Quality = m_Msaa4xEnable ? m_Msaa4xQuality - 1 : 0;
		dsvDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		dsvDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		D3D12_HEAP_PROPERTIES heapProperties;
		ZeroMemory(&heapProperties, sizeof(heapProperties));
		heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
		heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		heapProperties.CreationNodeMask = 1;
		heapProperties.VisibleNodeMask = 1;

		D3D12_CLEAR_VALUE clearValue;
		ZeroMemory(&clearValue, sizeof(clearValue));
		clearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		clearValue.DepthStencil.Depth = 1.0f;
		clearValue.DepthStencil.Stencil = 0;

		D3D12_DEPTH_STENCIL_VIEW_DESC dsViewDesc;
		dsViewDesc.Flags = D3D12_DSV_FLAG_NONE;
		dsViewDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsViewDesc.Texture2D.MipSlice = 0;
		m_Device->CreateDepthStencilView(m_DepthStencilBuffer, &dsViewDesc, GetDepthStencilView());

		HRESULT result = m_Device->CreateCommittedResource(&heapProperties, D3D12_HEAP_FLAG_NONE, &dsvDesc, D3D12_RESOURCE_STATE_COMMON,
			&clearValue, IID_PPV_ARGS(&m_DepthStencilBuffer));
		if (FAILED(result)) return false;

		D3D12_CPU_DESCRIPTOR_HANDLE cpuDescriptorHandle = m_DsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		m_Device->CreateDepthStencilView(m_DepthStencilBuffer, nullptr, cpuDescriptorHandle);

		return true;
	}

	void DirectX12::SetViewAndScissor()
	{
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;
		m_Viewport.Width = static_cast<float>(m_WindowInfo->m_Width);
		m_Viewport.Height = static_cast<float>(m_WindowInfo->m_Height);
		m_Viewport.MaxDepth = 1.0f;
		m_Viewport.MinDepth = 0.0f;

		m_ScissorRect = { 0, 0, static_cast<LONG>(m_WindowInfo->m_Width), static_cast<LONG>(m_WindowInfo->m_Height) };
	}

	void DirectX12::WaitForGpuCompelete()
	{
		UINT64 fenceValue = ++m_FenceValue[m_CurrentSwapChainBuffer];

		HRESULT result = m_CommandQueue->Signal(m_Fence, fenceValue);

		if (m_Fence->GetCompletedValue() < fenceValue)
		{
			result = m_Fence->SetEventOnCompletion(fenceValue, m_FenceEvent);
			WaitForSingleObject(m_FenceEvent, INFINITE);
		}
	}

	void DirectX12::MoveToNextFrame()
	{
		m_CurrentSwapChainBuffer = m_SwapChain->GetCurrentBackBufferIndex();

		WaitForGpuCompelete();
	}

	ID3D12Resource* DirectX12::GetCurrentBackBuffer() const
	{
		return m_RenderTargetBuffers[m_CurrentSwapChainBuffer];
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DirectX12::GetCurrentBackBufferView() const
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += (m_CurrentSwapChainBuffer * m_RtvDescriptorSize);
		return rtvHandle;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DirectX12::GetDepthStencilView() const
	{
		return m_DsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	}

	void DirectX12::BeginScene(const Vec4& color)
	{
		//Reset CommandAllocator, CommandList
		HRESULT result = m_CommandAllocator->Reset();
		result = m_CommandList->Reset(m_CommandAllocator, nullptr);

		//Indicate a state transition on the resource usage
		D3D12_RESOURCE_BARRIER resourceBarrier;
		resourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		resourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		resourceBarrier.Transition.pResource = GetCurrentBackBuffer();
		resourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		resourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		resourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		m_CommandList->ResourceBarrier(1, &resourceBarrier);

		//Set Viewport, scissor rect
		m_CommandList->RSSetViewports(1, &m_Viewport);
		m_CommandList->RSSetScissorRects(1, &m_ScissorRect);

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = GetCurrentBackBufferView();
		D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = GetDepthStencilView();

		//Clear render target view
		float clearColor[4] = { color.x, color.y, color.z, color.w };
		m_CommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

		//Clear depth stencil view
		m_CommandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

		//Connect RTV and DSV to OM
		m_CommandList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);

		ID3D12DescriptorHeap* descriptorHeaps[] = { m_CbvSrvUavDescriptorHeap };
		m_CommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	}

	void DirectX12::EndScene()
	{
		//Indicate a state transition on the resource usage
		D3D12_RESOURCE_BARRIER resourceBarrier;
		resourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		resourceBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		resourceBarrier.Transition.pResource = GetCurrentBackBuffer();
		resourceBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		resourceBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		resourceBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		m_CommandList->ResourceBarrier(1, &resourceBarrier);

		//Done recording commands
		HRESULT result = m_CommandList->Close();

		//Add the command list to queue for excution
		ID3D12CommandList* commandLists[] = { m_CommandList };
		m_CommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

		WaitForGpuCompelete();

		m_SwapChain->Present(1, 0);

		MoveToNextFrame();		
	}

	DirectX12* DirectX12::s_Instance = nullptr;
}
