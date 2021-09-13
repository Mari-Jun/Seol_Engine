#pragma once
#include "PARS/Layer/Layer.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	class DockLayer : public Layer
	{
	public:
		DockLayer(const std::string& name = "Dock Layer");
		virtual ~DockLayer() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void Update() override final;
	};
}


