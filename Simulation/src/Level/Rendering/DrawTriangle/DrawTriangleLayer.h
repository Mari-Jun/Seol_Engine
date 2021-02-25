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

	public:
		void SetTriMeshComp(const SPtr<class MeshComponent>& meshComp) { m_TriMeshComp = meshComp; }

	private:
		SPtr<class MeshComponent> m_TriMeshComp;
		APos m_Positions;
		ACol m_Colors;

	private:
		void TriangleDetail();
	};
}


