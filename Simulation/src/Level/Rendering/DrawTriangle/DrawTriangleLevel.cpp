#include "DrawTriangleLevel.h"
#include "DrawTriangleLayer.h"
#include "PARS/Component/Render/MeshComponent.h"

namespace PARS
{
	DrawTriangleLevel::DrawTriangleLevel()
		: Level("Draw Triangle Level")
	{
	}

	void DrawTriangleLevel::InitializeLevel()
	{
		auto layer = PARS::CreateSPtr<PARS::DrawTriangleLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		AddLayer(layer);

		auto actor = CreateSPtr<Actor>();
		auto meshComp = CreateSPtr<MeshComponent>();
		meshComp->SetHandMadeMesh<DiffuseMesh>(std::vector({
				DiffuseVertex(Vec3(0.0f, 0.5f, 0.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(0.5f, -0.5f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(-0.5f, -0.5f, 0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f))
				}));
		actor->AddComponent(meshComp);
		AddActor(actor);
	}

	void DrawTriangleLevel::UpdateLevel(float deltaTime)
	{
	}
}
