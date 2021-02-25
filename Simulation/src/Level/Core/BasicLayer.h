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
		virtual void Update() override final;
		virtual void ResizeLayer() override final;
		void OnDestroy(std::function<void()> func) { f_Destroy = func; }

	private:
		void UpdateObjects();
		virtual void UpdateDetail();
		void UpdateEndMenu();

	public:
		void AddObjectToLayer(std::string&& objectName);

	protected:
		void AddDetailFunction(std::string&& objectName, std::string&& triName, const std::function<void()>& function);

	private:
		bool m_IsOpen = true;
		ImGuiWindowFlags m_WindowFlags = 0;
		ImVec2 m_WindowSize;
		ImVec2 m_WindowPos;
		std::function<void()> f_Destroy;

	private:
		using NodeFunction = std::vector<std::pair<std::string, std::function<void()>>>;

		std::string m_SelectObject;
		std::vector<std::string> m_ObjectNames;
		std::unordered_map<std::string, NodeFunction> f_DetailFunctions;
	};
}


