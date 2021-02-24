#include "Camera2DLevel.h"
#include "PARS/Component/Render/MeshComponent.h"

namespace PARS
{
	Camera2DLevel::Camera2DLevel()
		: Level2D("Camera 2D Level")
	{
	}

	void Camera2DLevel::InitializeLevel()
	{
		Level2D::InitializeLevel();

		auto layer = PARS::CreateSPtr<PARS::Camera2DLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		layer->OnChangeMeshColor([this](const Vec4& color) {ChangeMeshColor(color); });
		layer->OnShowCameraPosition([this]() {PositionFunc(); });
		AddLayer(layer);

		m_Rectangle = CreateSPtr<Actor>();
		m_MeshComp = CreateSPtr<MeshComponent>();
		ChangeMeshColor(Vec4(0.0f, 1.0f, 0.0f, 1.0f));
		m_Rectangle->AddComponent(m_MeshComp);
		AddActor(m_Rectangle);
	}

	void Camera2DLevel::UpdateLevel(float deltaTime)
	{
	}

	void Camera2DLevel::ChangeMeshColor(const Vec4& meshColor)
	{
		m_MeshComp->SetHandMadeMesh<DiffuseMesh>(
			std::vector<DiffuseVertex>({ {Vec3(-200.0f, 200.0f, 0.0f), Vec4(meshColor)},
				{Vec3(200.0f, 200.0f, 0.0f), Vec4(meshColor)},
				{Vec3(200.0f, -200.0f, 0.0f), Vec4(meshColor)},
				{Vec3(-200.0f, -200.0f, 0.0f), Vec4(meshColor)} }),
			std::vector<UINT>({ 0,1,2,0,2,3 })
			);
	}

	void Camera2DLevel::PositionFunc()
	{
		static ImVec4 textColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		static ImVec4 buttonColor = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);

		const auto& cameraPos = std::reinterpret_pointer_cast<Actor>(GetDefaultPawn())->GetPosition();

		ImGui::TextColored(textColor, "Camera Position");
		std::ostringstream stream;
		stream << cameraPos;
		ImGui::BulletText(stream.str().c_str());

		ImGui::TextColored(textColor, "Rectangle Position");
		stream.str(""); stream.clear();
		stream << m_Rectangle->GetPosition();
		ImGui::BulletText(stream.str().c_str());
	

		ImGui::Separator();

		ImGui::TextColored(textColor, "Move Rectangle to CameraPos");
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.3f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.3f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.3f, 0.8f, 0.8f));
		if (ImGui::Button("Change Pos"))
		{
			m_Rectangle->SetPosition(Vec3(cameraPos.x, cameraPos.y, 0.0f));
		}
		ImGui::PopStyleColor(3);

	}
}
