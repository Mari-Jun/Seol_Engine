#pragma once
#include "PARS/Core/Core.h"
#include "PARS/Layer/Layer.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "PARS/Layer/EngineLayer/LayerHelper.h"

namespace PARS
{
	class EditLayer : public Layer
	{
	public:
		EditLayer(const std::string& name);
		virtual ~EditLayer() = default;

		virtual void Shutdown() override;
		virtual void Update() override final;
		virtual void UpdateEditLayer() {}

		virtual void AddLayer(const SPtr<Layer>& layer) override;

	protected:
		bool m_IsOpen = true;
		ImGuiID m_DockSpaceID;
		ImGuiWindowFlags m_DockWindowFlags;
		ImVec4 m_WindowBoxRect;

		std::vector<WPtr<Layer>> m_Layers;
	};
}



