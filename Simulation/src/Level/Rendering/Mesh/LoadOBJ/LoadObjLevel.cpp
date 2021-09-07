#include "LoadObjLevel.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"
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
		auto meshComp = CreateSPtr<StaticMeshComponent>();
		meshComp->SetMesh(CONTENT_DIR + "LoadObj\\Box");
		actor->AddComponent(meshComp);
		AddActor(actor);
	}

	void LoadObjLevel::UpdateLevel(float deltaTime)
	{
		
	}
}