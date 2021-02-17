#include "BasicLayer.h"

namespace PARS
{
	BasicLayer::BasicLayer(const std::string& name)
		: Layer(name)
	{
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

	void BasicLayer::BeginUpdate()
	{
		ImGui::Begin(m_LayerName.c_str(), &m_IsOpen);
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