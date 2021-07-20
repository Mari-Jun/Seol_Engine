#pragma once

#include <PARS.h>
#include "Level/Core/BasicLayer.h"

namespace PARS
{
	class Camera2DLayer : public DetailLayer
	{
	public:
		Camera2DLayer();
		virtual ~Camera2DLayer() = default;

		void Initialize() override;

	public:
		void SetRectangleActor(const SPtr<class Actor>& actor) { m_RectangleActor = actor; }
		void SetRectMeshComp(const SPtr<class MeshComponent>& meshComp) { m_RectMeshComp = meshComp; }

	private:
		SPtr<class Actor> m_RectangleActor;
		SPtr<class MeshComponent> m_RectMeshComp;
		Vec4 m_MeshColor;
	
	private:
		void RectangleActorDetail();
		void RectangleMeshCompDetail();

	public:
		void SetCameraActor(const SPtr<class Actor>& actor) { m_CameraActor = actor; }

	private:
		SPtr<class Actor> m_CameraActor;

	private:
		void CameraDetail();		
	};
}



