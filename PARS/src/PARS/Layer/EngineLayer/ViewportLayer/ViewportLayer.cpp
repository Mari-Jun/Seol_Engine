#include "stdafx.h"
#include "PARS/Layer/EngineLayer/LayerHelper.h"
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
			ImVec4 rect = IMGUIHELP::GetImGuiWindowSize();

			auto mainViewport = RenderFactory::GetRenderFactory()->GetViewport(0);
			mainViewport->SetLeft(static_cast<float>(rect.x));
			mainViewport->SetTop(static_cast<float>(rect.y));
			mainViewport->SetWidth(static_cast<float>(rect.z));
			mainViewport->SetHeight(static_cast<float>(rect.w));

			if(ImGui::IsWindowHovered())
				ImGui::GetForegroundDrawList()->AddRect(
					{ rect.x, rect.y }, { rect.x + rect.z, rect.y + rect.w }, IM_COL32(255, 255, 50, 255));
		}
		// ImGui::IsWindowHovered() 이거 클릭에 사용하면 좋을듯?
		ImGui::End();
	}
}
