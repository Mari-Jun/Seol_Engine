#include "Camera2DLayer.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	Camera2DLayer::Camera2DLayer()
		: BasicLayer("Camera 2D Layer")
		, m_MeshColor(COLOR::Green)
	{
	}

	void Camera2DLayer::Initialize()
	{
		AddDetailFunction("Rectangle", "Rectangle Actor", [this]() {RectangleActorDetail(); });
		AddDetailFunction("Rectangle", "MeshComponent", [this]() {RectangleMeshCompDetail(); });
		AddDetailFunction("Camera", "Camera Actor", [this]() {CameraDetail(); });
	}

	void Camera2DLayer::RectangleActorDetail()
	{
		const auto& cameraPos = m_CameraActor->GetPosition();

		static ImVec4 textColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
		static ImVec4 buttonColor = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);

		ImGui::TextColored(textColor, "Rectangle Position");
		std::ostringstream stream;
		stream << m_RectangleActor->GetPosition();
		ImGui::BulletText(stream.str().c_str());

		ImGui::TextColored(textColor, "Move Rectangle to CameraPos");
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.3f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.3f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.3f, 0.8f, 0.8f));
		if (ImGui::Button("Change Pos"))
		{
			m_RectangleActor->SetPosition(Vec3(cameraPos.x, cameraPos.y, 0.0f));
		}
		ImGui::PopStyleColor(3);
	}

	void Camera2DLayer::RectangleMeshCompDetail()
	{
		ImGui::ColorEdit3("Mesh Color", (float*)&m_MeshColor);

		m_RectMeshComp->SetHandMadeMesh<DiffuseMesh>(
			std::vector<DiffuseVertex>({ {Vec3(-200.0f, 200.0f, 0.0f), Vec4(m_MeshColor)},
				{Vec3(200.0f, 200.0f, 0.0f), Vec4(m_MeshColor)},
				{Vec3(200.0f, -200.0f, 0.0f), Vec4(m_MeshColor)},
				{Vec3(-200.0f, -200.0f, 0.0f), Vec4(m_MeshColor)} }),
			std::vector<UINT>({ 0,1,2,0,2,3 })
			);
	}

	void Camera2DLayer::CameraDetail()
	{
		const auto& cameraPos = m_CameraActor->GetPosition();

		static ImVec4 textColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);

		ImGui::TextColored(textColor, "Camera Position");
		std::ostringstream stream;
		stream << cameraPos;
		ImGui::BulletText(stream.str().c_str());
	}
}