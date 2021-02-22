#include "Camera2DLevel.h"
#include "PARS/Component/Render/MeshComponent.h"

namespace PARS
{
	Camera2DLevel::Camera2DLevel()
		: Level2D("Camera 2D Level")
	{
	}

	void Camera2DLevel::InitializeLevel()
	{
		Level2D::InitializeLevel();

		auto layer = PARS::CreateSPtr<PARS::Camera2DLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		AddLayer(layer);

		auto rectangle = CreateSPtr<Actor>();
		auto meshComp = CreateSPtr<MeshComponent>();
		meshComp->SetHandMadeMesh<DiffuseMesh>(std::vector({
				DiffuseVertex(Vec3(-200.0f, 200.0f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(200.0f, 200.0f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(200.0f, -200.0f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(-200.0f, 200.0f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(200.0f, -200.0f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(-200.0f, -200.0f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f))
			}));
		rectangle->AddComponent(meshComp);
		AddActor(rectangle);
	}

	void Camera2DLevel::UpdateLevel(float deltaTime)
	{
	}
}
