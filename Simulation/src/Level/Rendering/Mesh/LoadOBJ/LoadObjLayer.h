#pragma once
#include <PARS.h>
#include "Level/Core/BasicLayer.h"  

namespace PARS
{
	class LoadObjLayer : public BasicLayer
	{
	public:
		LoadObjLayer();
		virtual ~LoadObjLayer() = default;

		void Initialize() override;

	public:
		void SetMeshComp(const SPtr<class MeshComponent>& meshComp) { m_MeshComp = meshComp; }

	private:
		SPtr<class MeshComponent> m_MeshComp;

	private:
		void ObjDetail();
	};
}


