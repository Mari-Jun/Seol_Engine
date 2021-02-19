#pragma once

#include <PARS.h>
#include "Level/Core/BasicLayer.h"	

namespace PARS
{
	using APos = std::array<Vec3, 3>;
	using ACol = std::array<Vec4, 3>;

	class DrawTriangleLayer : public BasicLayer
	{
	public:
		DrawTriangleLayer();
		virtual ~DrawTriangleLayer() = default;

		void Initialize() override;
		void UpdateGUI() override;

		void OnChangeVertex(std::function<void(APos, ACol)> func) { f_ChangeVertex = func; }

	private:
		APos m_Positions;
		ACol m_Colors;

	private:
		std::function<void(APos, ACol)> f_ChangeVertex;
	};
}


