#include "DrawTriangleLayer.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	DrawTriangleLayer::DrawTriangleLayer()
		: BasicLayer("Draw Triangle Layer")
	{
	}

	void DrawTriangleLayer::Initialize()
	{
		m_Positions[0] = { 0.0f, 0.5f, 0.0f };
		m_Positions[1] = { 0.5f, -0.5f, 0.0f };
		m_Positions[2] = { -0.5f, -0.5f, 0.0f };

		m_Colors[0] = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_Colors[1] = { 0.0f, 1.0f, 0.0f, 1.0f };
		m_Colors[2] = { 0.0f, 0.0f, 1.0f, 1.0f };

		AddDetailFunction("Triangle", "MeshComponent", [this]() {TriangleDetail(); });
	}

	void DrawTriangleLayer::TriangleDetail()
	{
		ImGui::ColorEdit3("Color 1", (float*)&m_Colors[0]);
		ImGui::ColorEdit3("Color 2", (float*)&m_Colors[1]);
		ImGui::ColorEdit3("Color 3", (float*)&m_Colors[2]);

		ImGui::SliderFloat2("Position 1", (float*)&m_Positions[0], -1.0f, 1.0f);
		ImGui::SliderFloat2("Position 2", (float*)&m_Positions[1], -1.0f, 1.0f);
		ImGui::SliderFloat2("Position 3", (float*)&m_Positions[2], -1.0f, 1.0f);

		m_TriMeshComp->SetHandMadeMesh<DiffuseMesh>(
			std::vector<DiffuseVertex>({ {Vec3(m_Positions[0]),Vec4(m_Colors[0])},
				{Vec3(m_Positions[1]),Vec4(m_Colors[1])},
				{Vec3(m_Positions[2]),Vec4(m_Colors[2])} }));

	}
}
