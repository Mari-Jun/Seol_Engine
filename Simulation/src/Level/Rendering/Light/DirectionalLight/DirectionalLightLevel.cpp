#include "DirectionalLightLevel.h"
#include "PARS/Actor/Light/DirectionalLight/DirectionalLight.h"
#include "PARS/Component/Render/Mesh/Static/StaticMeshComp.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshComp.h"

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
		actor->SetScale(100.0f);
		AddActor(actor);
		auto meshComp = CreateSPtr<StaticMeshComponent>();
		meshComp->SetMesh(CONTENT_DIR + "Default\\Box");
		actor->AddComponent(meshComp);

		actor = CreateSPtr<Actor>("Tree");
		actor->SetPosition({ 200.0f, 0.0f, 1000.0f });
		actor->SetScale({ 500.0f, 100.0f, 500.0f });
		AddActor(actor);
		meshComp = CreateSPtr<StaticMeshComponent>();
		meshComp->SetMesh(CONTENT_DIR + "LoadObj\\Tree");
		actor->AddComponent(meshComp);

		actor = CreateSPtr<Actor>("Tree");
		actor->SetPosition({ -200.0f, 0.0f, 1000.0f });
		actor->SetScale(100.0f);
		AddActor(actor);
		meshComp = CreateSPtr<StaticMeshComponent>();
		meshComp->SetMesh(CONTENT_DIR + "LoadObj\\Tree2");
		actor->AddComponent(meshComp);

		auto light = CreateSPtr<DirectionalLight>("DirectionalLight");
		AddActor(light);

		auto rectangle = CreateSPtr<Actor>("Rectangle");
		auto hmeshComp = CreateSPtr<HandmadeMeshComponent>();
		hmeshComp->SetMesh(
			std::vector<DiffuseVertex>({ {Vec3(-200.0f, 200.0f, 0.0f), Vec4(COLOR::Green)},
				{Vec3(200.0f, 200.0f, 0.0f), Vec4(COLOR::Green)},
				{Vec3(200.0f, -200.0f, 0.0f), Vec4(COLOR::Green)},
				{Vec3(-200.0f, -200.0f, 0.0f), Vec4(COLOR::Green)} }),
			std::vector<UINT>({ 0,1,2,0,2,3 })
		);
		rectangle->AddComponent(hmeshComp);
		AddActor(rectangle);
	}

	void DirectionalLightLevel::UpdateLevel(float deltaTime)
	{
		/*static float time = 0.0f;
		static float move = 100.0f;

		time += deltaTime;

		if (time > 0.02f && move <= 1100.0f)
		{
			auto actor = CreateSPtr<Actor>("Tree");
			actor->SetPosition({ move, 0.0f, 1000.0f - move });
			actor->SetScale(100.0f);
			AddActor(actor);
			auto meshComp = CreateSPtr<StaticMeshComponent>();
			meshComp->SetMesh(CONTENT_DIR + "LoadObj\\Tree");
			actor->AddComponent(meshComp);

			time -= 0.02f;
			move += 1.0f;
		}*/
	}
}