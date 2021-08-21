#include "DirectionalLightLevel.h"
#include "PARS/Actor/Light/DirectionalLight/DirectionalLight.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"

namespace PARS
{
	DirectionalLightLevel::DirectionalLightLevel()
		: Level3D("Directional Light Level")
	{
	}

	void DirectionalLightLevel::InitializeLevel()
	{
		Level3D::InitializeLevel();

		auto actor = CreateSPtr<Actor>("Cube");
		actor->SetPosition({ 0.0f, 0.0f, 1000.0f });
		actor->SetScale(400.0f);
		AddActor(actor);
		auto meshComp = CreateSPtr<StaticMeshComponent>();
		meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, CONTENT_DIR + "Default\\Box.obj");
		actor->AddComponent(meshComp);

		actor = CreateSPtr<Actor>("Tree");
		actor->SetPosition({ 500.0f, 0.0f, 1000.0f });
		actor->SetScale(400.0f);
		AddActor(actor);
		meshComp = CreateSPtr<StaticMeshComponent>();
		meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, CONTENT_DIR + "LoadObj\\Tree.obj");
		actor->AddComponent(meshComp);

		actor = CreateSPtr<Actor>("Tree");
		actor->SetPosition({ -500.0f, 0.0f, 1000.0f });
		actor->SetScale(400.0f);
		AddActor(actor);
		meshComp = CreateSPtr<StaticMeshComponent>();
		meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, CONTENT_DIR + "LoadObj\\Tree.obj");
		actor->AddComponent(meshComp);

		auto light = CreateSPtr<DirectionalLight>("DirectionalLight");
		AddActor(light);
	}

	void DirectionalLightLevel::UpdateLevel(float deltaTime)
	{
	}
}