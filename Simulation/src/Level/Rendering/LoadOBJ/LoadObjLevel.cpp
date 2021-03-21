#include "LoadObjLevel.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"
#include "PARS/Component/Light/LightComponent.h"

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
		actor->SetScale(400.0f);
		auto meshComp = CreateSPtr<MeshComponent>();
		meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, "LoadObj/Box");
		actor->AddComponent(meshComp);
		AddActor(actor);

		auto layer = PARS::CreateSPtr<PARS::LoadObjLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		layer->AddObjectToLayer("Obj");
		layer->SetMeshComp(meshComp);
		AddLayer(layer);

		auto light = CreateSPtr<Actor>();
		auto lightComp = CreateSPtr<LightComponent>();
		light->AddComponent(lightComp);
		AddActor(light);
	}

	void LoadObjLevel::UpdateLevel(float deltaTime)
	{
		
	}
}