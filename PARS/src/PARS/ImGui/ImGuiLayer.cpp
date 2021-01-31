#include "stdafx.h"
#include "PARS/ImGui/ImGuiLayer.h"	
#include "PARS/Renderer/DirectX12/DirectX12.h"

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_dx12.h"

namespace PARS
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		
	}

	void ImGuiLayer::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		const auto& windowInfo = Window::GetWindowInfo();
		const auto& directX12 = DirectX12::GetDirectX12();
		const auto& device = directX12->GetDevice();
		const auto& srvHeap = directX12->GetSrvHeap();

		ImGui_ImplWin32_Init(windowInfo->m_hwnd);
		ImGui_ImplDX12_Init(device, 2, DXGI_FORMAT_R8G8B8A8_UNORM, srvHeap,
			srvHeap->GetCPUDescriptorHandleForHeapStart(),
			srvHeap->GetGPUDescriptorHandleForHeapStart());
	}

	void ImGuiLayer::Shutdown()
	{
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Update()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	

	void ImGuiLayer::Draw()
	{
		const auto& directX12 = DirectX12::GetDirectX12();

		ID3D12GraphicsCommandList* commandList = directX12->GetCommandList();
		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);		

		// Update and Render additional Platform Windows
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault(NULL, (void*)commandList);
		}
	}
}
