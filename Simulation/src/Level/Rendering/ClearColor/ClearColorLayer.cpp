#include "ClearColorLayer.h"
#include <imgui/imgui.h>

namespace PARS
{
	ClearColorLayer::ClearColorLayer()
		: BasicLayer("Clear Color Layer")
	{
	
	}

	void ClearColorLayer::UpdateGUI()
	{
		static Vec4 clearColor;
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		Renderer::SetClearColor(clearColor);
	}
}
