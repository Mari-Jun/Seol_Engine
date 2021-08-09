#include "stdafx.h"
#include "PARS/Layer/EngineLayer/ViewportLayer/ViewportLayer.h"

namespace PARS
{
	ViewportLayer::ViewportLayer(const std::string& name)
		: Layer(name)
	{
	}

	void ViewportLayer::Shutdown()
	{
	}

	void ViewportLayer::Update()
	{
		if (ImGui::Begin("Viewport Layer", nullptr, m_WindowFlags))
		{
			
		}
		m_WindowSize = ImGui::GetItemRectSize();
		ImGui::End();
	}
}
