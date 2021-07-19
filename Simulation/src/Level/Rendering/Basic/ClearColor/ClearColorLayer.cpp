#include "ClearColorLayer.h"

namespace PARS
{
	ClearColorLayer::ClearColorLayer()
		: BasicLayer("Clear Color Layer")
	{
	
	}

	void ClearColorLayer::UpdateDetail()
	{
		static Vec4 clearColor;
		ImGui::ColorEdit3("clear color", (float*)&clearColor);
		Renderer::SetClearColor(clearColor);
	}
}
