#include "stdafx.h"
#include "PARS/Layer/EngineLayer/ViewportLayer/ViewportLayer.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Renderer/Core/RenderFactory.h"

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
		ImGui::SetNextWindowBgAlpha(0.0f);
		if (ImGui::Begin("Viewport Layer", nullptr, m_WindowFlags))
		{
			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			ImVec2 vMax = ImGui::GetWindowContentRegionMax();

			vMin.x += ImGui::GetWindowPos().x - ImGui::GetStyle().WindowPadding.x;
			vMin.y += ImGui::GetWindowPos().y - ImGui::GetStyle().WindowPadding.y;
			vMax.x += ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x;
			vMax.y += ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y;

			auto mainViewport = RenderFactory::GetRenderFactory()->GetViewport(0);
			mainViewport->SetLeft(static_cast<float>(vMin.x));
			mainViewport->SetTop(static_cast<float>(vMin.y));
			mainViewport->SetWidth(static_cast<float>(vMax.x - vMin.x));
			mainViewport->SetHeight(static_cast<float>(vMax.y - vMin.y));

			if(ImGui::IsWindowHovered())
				ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 50, 255));
		}
		// ImGui::IsWindowHovered() 이거 클릭에 사용하면 좋을듯?
		ImGui::End();
	}
}
