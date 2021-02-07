#include "ClearColorLayer.h"
#include <imgui/imgui.h>

namespace PARS
{
	ClearColorLayer::ClearColorLayer()
		: Layer("Clear Color Layer")
	{
	
	}

	void ClearColorLayer::Update()
	{
		ImGui::Begin("Clear Color");

		static Vec4 clearColor;
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		Renderer::SetClearColor(clearColor);

		ImGui::End();
	}
}
