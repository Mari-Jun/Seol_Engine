#include "DirectionalLightLevel.h"
#include "PARS/Actor/Light/DirectionalLight/DirectionalLight.h"
#include "PARS/Component/Render/Mesh/MeshComponent.h"

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
		auto meshComp = CreateSPtr<MeshComponent>();
		meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, "LoadObj/Tree");
		actor->AddComponent(meshComp);
		AddActor(actor);

		/*auto layer = PARS::CreateSPtr<PARS::DirectionalLightLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		layer->AddObjectToLayer("Obj");
		layer->SetMeshComp(meshComp);
		AddLayer(layer);*/

		auto light = CreateSPtr<DirectionalLight>("DirectionalLight");
		AddActor(light);
	}

	void DirectionalLightLevel::UpdateLevel(float deltaTime)
	{
		static float time = 0.0f;
		static SPtr<Actor> cube = nullptr;

		time += deltaTime;

		if (time > 0.5f &&  cube == nullptr)
		{
			cube = CreateSPtr<Actor>("Cube");
			cube->SetPosition({ 500.0f, 0.0f, 1000.0f });
			cube->SetScale(400.0f);
			auto meshComp = CreateSPtr<MeshComponent>();
			meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, "LoadObj/Tree");
			cube->AddComponent(meshComp);
			AddActor(cube);
		}
		else if (time > 1.0f)
		{
			cube->SetActorState(Actor::ActorState::Dead);
			cube = nullptr;
			time -= 1.0f;			
		}


	}
}