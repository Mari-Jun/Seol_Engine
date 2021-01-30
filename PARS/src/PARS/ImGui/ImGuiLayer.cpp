#include "stdafx.h"
#include "PARS/Core/Window.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/ImGui/ImGuiLayer.h"	

#include "imgui.h"
#include "PARS/ImGui/imgui_impl_win32.h"
#include "PARS/ImGui/imgui_impl_dx12.h"

namespace PARS
{
	ImGuiLayer::ImGuiLayer(const WindowInfo& info, const WPtr<DirectX12>& directX12)
		: Layer("ImGuiLayer")
		, m_WindowInfo(info), m_DirectX12(directX12)
	{
		PARS_ERROR("SSS");
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

		const auto& device = m_DirectX12.lock()->GetDevice();
		const auto& srvHeap = m_DirectX12.lock()->GetSrvHeap();

		ImGui_ImplWin32_Init(m_WindowInfo.m_hwnd);
		ImGui_ImplDX12_Init(device, 2, DXGI_FORMAT_R8G8B8A8_UNORM, srvHeap,
			srvHeap->GetCPUDescriptorHandleForHeapStart(),
			srvHeap->GetGPUDescriptorHandleForHeapStart());
	}

	void ImGuiLayer::Shutdown()
	{
		ImGui_ImplDX12_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		SetStateDead();
	}

	void ImGuiLayer::Update()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
	

	void ImGuiLayer::Draw()
	{

		ID3D12GraphicsCommandList* commandList = m_DirectX12.lock()->GetCommandList();
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
