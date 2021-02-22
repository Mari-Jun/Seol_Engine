#include "DrawTriangleLevel.h"

namespace PARS
{
	DrawTriangleLevel::DrawTriangleLevel()
		: Level2D("Draw Triangle Level")
	{

	}

	void DrawTriangleLevel::InitializeLevel()
	{
		Level2D::InitializeLevel();

		auto layer = PARS::CreateSPtr<PARS::DrawTriangleLayer>();
		layer->OnDestroy([this]() {Destroy(); });
		layer->OnChangeVertex([this](APos pos, ACol color) {ChangeVertexPosition(pos, color); });
		AddLayer(layer);

		auto actor = CreateSPtr<Actor>();
		m_MeshComp = CreateSPtr<MeshComponent>();
		m_MeshComp->SetHandMadeMesh<DiffuseMesh>(std::vector({
				DiffuseVertex(Vec3(0.0f, 0.5f, 0.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(0.5f, -0.5f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f)),
				DiffuseVertex(Vec3(-0.5f, -0.5f, 0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f))
				}));
		actor->AddComponent(m_MeshComp);
		AddActor(actor);

		SetRenderProjectionOrtho(-1.0f, 1.0f, -1.0f, 1.0f);
	}

	void DrawTriangleLevel::UpdateLevel(float deltaTime)
	{

	}

	void DrawTriangleLevel::ChangeVertexPosition(APos pos, ACol color)
	{
		m_MeshComp->SetHandMadeMesh<DiffuseMesh>(std::vector({
			DiffuseVertex(std::move(pos[0]), std::move(color[0])),
			DiffuseVertex(std::move(pos[1]), std::move(color[1])),
			DiffuseVertex(std::move(pos[2]), std::move(color[2]))
			}));
	}
}
