#pragma once
#include "PARS/Layer/Layer.h"
#include "PARS/Layer/EngineLayer/DetailLayer/DetailFunctionFactory.h"
#include "imgui.h"

namespace PARS
{
	struct DetailObject
	{
		std::string name;
		std::vector<FunctionInfo> detailFunctions;
		int index = 1;
	};

	class DetailLayer : public Layer
	{
	public:
		DetailLayer(const std::string& name = "Detail Layer");
		virtual ~DetailLayer() = default;

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
		void AddObjectToLayer(DetailObject& object);
		void RemoveObjectToLayer(const std::string& name);

	private:
		bool m_IsOpen = true;
		ImGuiWindowFlags m_WindowFlags = 0;
		ImVec2 m_WindowSize;
		ImVec2 m_WindowPos;
		std::function<void()> f_Destroy;

	private:
		std::string m_SelectObjectName;
		DetailObject m_SelectObject;
		std::multimap<std::string, DetailObject> m_DetailObjects;
	};
}


