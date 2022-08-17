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

			//�����ٶ� �ӽ÷� �̸����� �ҷ�����.
			auto camera = RenderFactory::GetRenderFactory()->GetCameraComp("Default Pawn 1");
			if (camera != nullptr)
			{
				camera->UpdateViewportSize(static_cast<float>(rect.x), static_cast<float>(rect.y),
					static_cast<float>(rect.z), static_cast<float>(rect.w));
			}

			if(ImGui::IsWindowHovered())
				ImGui::GetForegroundDrawList()->AddRect(
					{ rect.x, rect.y }, { rect.x + rect.z, rect.y + rect.w }, IM_COL32(255, 255, 50, 255));
		}
		// ImGui::IsWindowHovered() �̰� Ŭ���� ����ϸ� ������?
		ImGui::End();
	}
}
