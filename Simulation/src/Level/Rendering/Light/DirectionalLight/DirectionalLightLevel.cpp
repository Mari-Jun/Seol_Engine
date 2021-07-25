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
		meshComp->SetMesh<DiffuseMesh>(MeshComponent::FileType::Obj, "Default/Box");
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
		
	}
}