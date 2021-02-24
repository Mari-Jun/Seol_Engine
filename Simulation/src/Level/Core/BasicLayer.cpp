#include "BasicLayer.h"

namespace PARS
{
	BasicLayer::BasicLayer(const std::string& name)
		: Layer(name)
	{
		m_WindowFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
		ResizeLayer();	
	}

	void BasicLayer::Update()
	{
		BeginUpdate();
		UpdateGUI();
		EndUpdate();
	}

	void BasicLayer::Shutdown()
	{
		Renderer::SetClearColor(COLOR::Gray);
		f_Destroy();
	}

	void BasicLayer::ResizeLayer()
	{
		RECT rect;
		GetWindowRect(Window::GetWindowInfo()->m_hwnd, &rect);

		m_WindowSize = ImVec2(static_cast<float>(Window::GetWindowInfo()->m_LayerWidth), static_cast<float>(Window::GetWindowInfo()->m_Height));

		float x = rect.right - m_WindowSize.x - 7.5f;
		float y = rect.top + static_cast<float>(GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));

		m_WindowPos = ImVec2(x, y);
	}

	void BasicLayer::BeginUpdate()
	{
		ImGui::SetNextWindowPos(m_WindowPos);
		ImGui::SetNextWindowSize(m_WindowSize);

		ImGui::Begin(m_LayerName.c_str(), false, m_WindowFlags);
	}

	void BasicLayer::EndUpdate()
	{
		ImGui::Separator();
		if (ImGui::Button("Return To Menu", ImVec2(150, 50)))
		{
			m_IsOpen = false;
		}

		ImGui::End();

		if (!m_IsOpen)
		{
			Destroy();
		}
	}
}