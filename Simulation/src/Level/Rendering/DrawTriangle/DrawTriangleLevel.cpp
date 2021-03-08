#include "DrawTriangleLevel.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

namespace PARS
{
	DrawTriangleLevel::DrawTriangleLevel()
		: Level2D("Draw Triangle Level")
	{

	}

	void DrawTriangleLevel::InitializeLevel()
	{
		Level2D::InitializeLevel();

		auto actor = CreateSPtr<Actor>();
		auto meshComp = CreateSPtr<MeshComponent>();
		meshComp->SetHandMadeMesh<DiffuseMesh>(std::vector({
				DiffuseVertex(Vec3(0.0f, 0.5f, 0.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(0.5f, -0.5f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(-0.5f, -0.5f, 0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f))
				}));
		actor->AddComponent(meshComp);
		AddActor(actor);
		
		auto layer = PARS::CreateSPtr<PARS::DrawTriangleLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		layer->AddObjectToLayer("Triangle");
		layer->SetTriMeshComp(meshComp);
		AddLayer(layer);
		

		SetRenderProjectionOrtho(-1.0f, 1.0f, -1.0f, 1.0f);
		SetDefaultControllerKeyEvent(false);
	}

	void DrawTriangleLevel::UpdateLevel(float deltaTime)
	{

	}
}
