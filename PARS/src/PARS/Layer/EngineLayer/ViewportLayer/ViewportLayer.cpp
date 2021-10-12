#include "stdafx.h"
#include "PARS/Layer/EngineLayer/LayerHelper.h"
#include "PARS/Layer/EngineLayer/ViewportLayer/ViewportLayer.h"
#include "PARS/Renderer/DirectX12/DirectX12.h"
#include "PARS/Renderer/Core/RenderFactory.h"
#include "PARS/Component/Camera/CameraComponent.h"


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

			//수정바람 임시로 이름으로 불러왔음.
			auto camera = RenderFactory::GetRenderFactory()->GetCameraComp("DefaultPawn 1");
			if (camera != nullptr)
			{
				camera->UpdateViewportSize(static_cast<float>(rect.x), static_cast<float>(rect.y),
					static_cast<float>(rect.z), static_cast<float>(rect.w));
			}

			if(ImGui::IsWindowHovered())
				ImGui::GetForegroundDrawList()->AddRect(
					{ rect.x, rect.y }, { rect.x + rect.z, rect.y + rect.w }, IM_COL32(255, 255, 50, 255));
		}
		// ImGui::IsWindowHovered() 이거 클릭에 사용하면 좋을듯?
		ImGui::End();
	}
}
