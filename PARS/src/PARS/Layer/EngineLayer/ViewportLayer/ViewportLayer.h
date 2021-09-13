#pragma once
#include "PARS/Layer/Layer.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	class ViewportLayer : public Layer
	{
	public:
		ViewportLayer(const std::string& name = "Viewport Layer");
		virtual ~ViewportLayer() = default;

		virtual void Initialize() override {}
		virtual void Shutdown() override;
		virtual void Update() override final;

	private:
		ImGuiWindowFlags m_WindowFlags = 0;
	};

}

