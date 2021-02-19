#include "DrawTriangleLayer.h"

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
	}

	void DrawTriangleLayer::UpdateGUI()
	{
		ImGui::ColorEdit3("Vertex Color 1", (float*)&m_Colors[0]);
		ImGui::ColorEdit3("Vertex Color 2", (float*)&m_Colors[1]);
		ImGui::ColorEdit3("Vertex Color 3", (float*)&m_Colors[2]);

		ImGui::SliderFloat2("Vertex Position 1", (float*)&m_Positions[0], -1.0f, 1.0f);
		ImGui::SliderFloat2("Vertex Position 2", (float*)&m_Positions[1], -1.0f, 1.0f);
		ImGui::SliderFloat2("Vertex Position 3", (float*)&m_Positions[2], -1.0f, 1.0f);

		f_ChangeVertex(m_Positions, m_Colors);
	}
}
