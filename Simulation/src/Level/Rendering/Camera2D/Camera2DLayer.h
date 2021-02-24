#pragma once

#include <PARS.h>
#include "Level/Core/BasicLayer.h"

namespace PARS
{
	class Camera2DLayer : public BasicLayer
	{
	public:
		Camera2DLayer();
		virtual ~Camera2DLayer() = default;

		void Initialize() override;
		void UpdateGUI() override;

		void OnChangeMeshColor(const std::function<void(const Vec4&)>& func) { f_ChangeMeshColor = func; }
		void OnShowCameraPosition(const std::function<void()>& func) { f_Position = func; }

	private:
		Vec4 m_MeshColor;

	private:
		std::function<void(const Vec4&)> f_ChangeMeshColor;
		std::function<void()> f_Position;
	};
}



