#pragma once
#include "PARS/Layer/Layer.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	class InterfaceLayer : public Layer
	{
	public:
		InterfaceLayer(const std::string& name = "Interface Layer");
		virtual ~InterfaceLayer() = default;

		virtual void Update() override final;

	private:
		ImGuiWindowFlags m_WindowFlags = 0;
	};
}


