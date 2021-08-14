#include "ClearColorLevel.h"

namespace PARS
{
	ClearColorLevel::ClearColorLevel()
		: Level("Clear Color")
	{
	}

	ClearColorLevel::~ClearColorLevel()
	{
	}

	void ClearColorLevel::InitializeLevel()
	{
		auto actor = CreateSPtr<Actor>("Clear Color");
		actor->SetIsUseDefaultDetail(false);
		actor->AddDetailFunctionInfo(FunctionInfo{ actor->GetActorName(), [this]() {
			static Vec4 clearColor;
			ImGui::ColorEdit3("clear color", (float*)&clearColor);
			Renderer::SetClearColor(clearColor);
			} });
		AddActor(actor);
	}

	void ClearColorLevel::UpdateLevel(float deltaTime)
	{
	
	}
}
