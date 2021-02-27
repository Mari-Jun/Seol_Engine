#include "LoadObjLevel.h"
#include "PARS/Component/Render/MeshComponent.h"

namespace PARS
{
	LoadObjLevel::LoadObjLevel()
		: Level3D("Load OBJ Level")
	{
	}

	void LoadObjLevel::InitializeLevel()
	{
		Level3D::InitializeLevel();

		auto actor = CreateSPtr<Actor>();
		actor->SetPosition({ 0.0f, 0.0f, 1000.0f });
		auto meshComp = CreateSPtr<MeshComponent>();
		meshComp->SetHandMadeMesh<DiffuseMesh>(
			std::vector({DiffuseVertex(Vec3(200.0f, 200.0f, 200.0f), Vec4(COLOR::Cyan)),
				DiffuseVertex(Vec3(200.0f, -200.0f, 200.0f), Vec4(COLOR::Cyan)),
				DiffuseVertex(Vec3(-200.0f, 200.0f, 200.0f), Vec4(COLOR::Cyan)),
				DiffuseVertex(Vec3(-200.0f, -200.0f, 200.0f), Vec4(COLOR::Cyan)),
				DiffuseVertex(Vec3(200.0f, 200.0f, -200.0f), Vec4(COLOR::Cyan)),
				DiffuseVertex(Vec3(200.0f, -200.0f, -200.0f), Vec4(COLOR::Cyan)),
				DiffuseVertex(Vec3(-200.0f, 200.0f, -200.0f), Vec4(COLOR::Cyan)),
				DiffuseVertex(Vec3(-200.0f, -200.0f, -200.0f), Vec4(COLOR::Cyan))}), 
				std::vector<UINT>({ 0,2,1,1,2,3,0,4,6,0,6,2,0,1,5,0,5,4,2,6,7,2,7,3,2,7,5,2,3,7,4,5,7,4,7,6 })
			);
		actor->AddComponent(meshComp);
		AddActor(actor);

		auto layer = PARS::CreateSPtr<PARS::LoadObjLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		layer->AddObjectToLayer("Box");
		AddLayer(layer);
	}

	void LoadObjLevel::UpdateLevel(float deltaTime)
	{
		
	}
}