#include "Camera2DLayer.h"

namespace PARS
{
	Camera2DLayer::Camera2DLayer()
		: BasicLayer("Camera 2D Layer")
		, m_MeshColor(COLOR::Green)
	{
	}

	void Camera2DLayer::Initialize()
	{
	}

	void Camera2DLayer::UpdateGUI()
	{
		ImGui::ColorEdit3("Mesh Color", (float*)&m_MeshColor);

		f_ChangeMeshColor(m_MeshColor);

		ImGui::Separator();

		f_Position();
	}
}