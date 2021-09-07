#include "DrawTriangleLevel.h"
#include "PARS/Component/Render/Mesh/Handmade/HandmadeMeshComp.h"

namespace PARS
{
	DrawTriangleLevel::DrawTriangleLevel()
		: Level2D("Draw Triangle Level")
	{

	}

	void DrawTriangleLevel::InitializeLevel()
	{
		Level2D::InitializeLevel();

		std::reinterpret_pointer_cast<Actor>(m_DefaultPawn)->SetDetailVisibleState(DVS::HideAll);
		std::reinterpret_pointer_cast<Actor>(m_DefaultController)->SetDetailVisibleState(DVS::HideAll);

		auto actor = CreateSPtr<Actor>("Triangle");
		AddActor(actor);
		actor->SetDetailVisibleState(DVS::Hide);
		auto meshComp = CreateSPtr<HandmadeMeshComponent>();

		static Vec4 colors[3] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} };
		static Vec3 positions[3] = { {0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f} };

		meshComp->SetMesh(std::vector({
				DiffuseVertex(Vec3(positions[0]), Vec4(colors[0])),
				DiffuseVertex(Vec3(positions[1]), Vec4(colors[1])),
				DiffuseVertex(Vec3(positions[2]), Vec4(colors[2]))
			}));
		actor->AddComponent(meshComp);
		
		SetDefaultControllerKeyEvent(false);
	}

	void DrawTriangleLevel::UpdateLevel(float deltaTime)
	{

	}
}
