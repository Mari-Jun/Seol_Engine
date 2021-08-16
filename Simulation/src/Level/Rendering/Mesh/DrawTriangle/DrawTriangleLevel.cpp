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

		std::reinterpret_pointer_cast<Actor>(m_DefaultPawn)->SetDetailVisibleState(DVS::HideAll);
		std::reinterpret_pointer_cast<Actor>(m_DefaultController)->SetDetailVisibleState(DVS::HideAll);

		auto actor = CreateSPtr<Actor>("Triangle");
		AddActor(actor);
		auto meshComp = CreateSPtr<MeshComponent>();
		actor->SetDetailVisibleState(DVS::Hide);

		static Vec4 colors[3] = { {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} };
		static Vec3 positions[3] = { {0.0f, 0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f} };

		meshComp->SetHandMadeMesh<DiffuseMesh>(std::vector({
				DiffuseVertex(Vec3(positions[0]), Vec4(colors[0])),
				DiffuseVertex(Vec3(positions[1]), Vec4(colors[1])),
				DiffuseVertex(Vec3(positions[2]), Vec4(colors[2]))
			}));
		actor->AddComponent(meshComp);
		meshComp->SetDetailVisibleState(DVS::HideDefault);
		meshComp->AddDetailFunctionInfo(FunctionInfo{ "Change Position/Color", [this, meshComp]() {

			ImGui::ColorEdit3("Color 1", (float*)&colors[0]);
			ImGui::ColorEdit3("Color 2", (float*)&colors[1]);
			ImGui::ColorEdit3("Color 3", (float*)&colors[2]);

			ImGui::SliderFloat2("Position 1", (float*)&positions[0], -1.0f, 1.0f);
			ImGui::SliderFloat2("Position 2", (float*)&positions[1], -1.0f, 1.0f);
			ImGui::SliderFloat2("Position 3", (float*)&positions[2], -1.0f, 1.0f);

			meshComp->SetHandMadeMesh<DiffuseMesh>(
				std::vector<DiffuseVertex>({ {Vec3(positions[0]),Vec4(colors[0])},
					{Vec3(positions[1]),Vec4(colors[1])},
					{Vec3(positions[2]),Vec4(colors[2])} }));
			}, false });
		
		SetRenderProjectionOrtho(-1.0f, 1.0f, -1.0f, 1.0f);
		SetDefaultControllerKeyEvent(false);
	}

	void DrawTriangleLevel::UpdateLevel(float deltaTime)
	{

	}
}
