#pragma once

#include <PARS.h>
#include "DrawTriangleLayer.h"
#include "PARS/Component/Render/MeshComponent.h"

namespace PARS
{
	class DrawTriangleLevel : public Level
	{
	public:
		DrawTriangleLevel();
		virtual ~DrawTriangleLevel() = default;

		void InitializeLevel() override;
		void UpdateLevel(float deltaTime) override;

		void ChangeVertexPosition(APos pos, ACol color);

	private:
		SPtr<MeshComponent> m_MeshComp;
	};
}


