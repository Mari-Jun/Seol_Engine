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

		static Vec4 clearColor;
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		Renderer::SetClearColor(clearColor);

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
