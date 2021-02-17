#pragma once

#include <PARS.h>
#include <imgui/imgui.h>

namespace PARS
{
	class BasicLayer : public Layer
	{
	public:
		BasicLayer(const std::string& name);
		virtual ~BasicLayer() = default;

		virtual void Initialize() override {}
		virtual void Shutdown() override;
		virtual void BeginUpdate();

		void OnDestroy(std::function<void()> func) { f_Destroy = func; }

	private:
		void Update() override;
		virtual void UpdateGUI() {};
		virtual void EndUpdate();

	private:
		bool m_IsOpen = true;
		std::function<void()> f_Destroy;
	};
}


