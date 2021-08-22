#include "Camera2DLevel.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshComp.h"

namespace PARS
{
	Camera2DLevel::Camera2DLevel()
		: Level2D("Camera 2D Level")
	{
	}

	void Camera2DLevel::InitializeLevel()
	{
		Level2D::InitializeLevel();

		auto rectangle = CreateSPtr<Actor>("Rectangle");
		auto meshComp = CreateSPtr<HandmadeMeshComponent>(); 
		meshComp->SetMesh<DiffuseMesh>(
			std::vector<DiffuseVertex>({ {Vec3(-200.0f, 200.0f, 0.0f), Vec4(COLOR::Green)},
				{Vec3(200.0f, 200.0f, 0.0f), Vec4(COLOR::Green)},
				{Vec3(200.0f, -200.0f, 0.0f), Vec4(COLOR::Green)},
				{Vec3(-200.0f, -200.0f, 0.0f), Vec4(COLOR::Green)} }),
			std::vector<UINT>({ 0,1,2,0,2,3 })
			);
		rectangle->AddComponent(meshComp);
		AddActor(rectangle);
	}

	void Camera2DLevel::UpdateLevel(float deltaTime)
	{
	}
}
