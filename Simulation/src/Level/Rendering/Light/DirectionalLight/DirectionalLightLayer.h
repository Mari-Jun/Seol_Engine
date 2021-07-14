#pragma once
#include <PARS.h>
#include "Level/Core/BasicLayer.h"  

namespace PARS
{
	class DirectionalLightLayer : public BasicLayer
	{
	public:
		DirectionalLightLayer();
		virtual ~DirectionalLightLayer() = default;

		void Initialize() override;

	public:
		void SetMeshComp(const SPtr<class MeshComponent>& meshComp) { m_MeshComp = meshComp; }
		void SetLightComp(const SPtr<class LightComponent>& lightComp) { m_LightComp = lightComp; }

	private:
		SPtr<class MeshComponent> m_MeshComp;
		SPtr<class LightComponent> m_LightComp;
		Vec3 m_LightColor;

	private:
		void ObjDetail();
		void DirectionalLightDetail();
	};
}


