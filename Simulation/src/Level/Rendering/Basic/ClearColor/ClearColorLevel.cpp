#include "ClearColorLevel.h"

namespace PARS
{
	ClearColorLevel::ClearColorLevel()
		: Level("Clear Color Level")
	{
	}

	ClearColorLevel::~ClearColorLevel()
	{
	}

	void ClearColorLevel::InitializeLevel()
	{
		AddLevelSettingFunctionInfo(FunctionInfo{ "Clear Color", [this]() {
			static Vec4 clearColor;
			ImGui::ColorEdit3("clear color", (float*)&clearColor);
			Renderer::SetClearColor(clearColor);
			} });
	}

	void ClearColorLevel::ShutdownLevel()
	{
		Renderer::SetClearColor(COLOR::Gray);
	}

	void ClearColorLevel::UpdateLevel(float deltaTime)
	{
	
	}
}
