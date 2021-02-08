#include "ClearColorLayer.h"
#include <imgui/imgui.h>

namespace PARS
{
	ClearColorLayer::ClearColorLayer()
		: Layer("Clear Color Layer")
	{
	
	}

	ClearColorLayer::~ClearColorLayer()
	{
	}

	void ClearColorLayer::Update()
	{
		bool open = true;
		ImGui::Begin(m_LayerName.c_str(), &open);

		static Vec4 clearColor = COLOR::Black;
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		Renderer::SetClearColor(clearColor);

		ImGui::Separator();
		if (ImGui::Button("Return To Menu", ImVec2(150, 50)))
		{
			open = false;
		}

		ImGui::End();

		if (!open)
		{
			Destroy();
		}
	}

	void ClearColorLayer::Shutdown()
	{
		Renderer::SetClearColor(COLOR::Black);
		f_Destroy();
	}
}
