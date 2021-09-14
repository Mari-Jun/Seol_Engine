#pragma once
#include "PARS/Layer/Layer.h"
#include "imgui.h"

namespace PARS
{
	class ContentLayer : public Layer
	{
	public:
		ContentLayer(const std::string& name = "Content Layer");
		virtual ~ContentLayer() = default;

		virtual void Initialize() override;
		virtual void Shutdown() override;
		virtual void LayerInput() override;
		virtual void Update() override final;

	private:
		bool m_IsUpdateContentView = true;

	public:
		void AddNewContent() { m_IsUpdateContentView = true; }

	private:
		void UpdateFolderList();
		void RecursiveFolderList(const std::filesystem::path& path);
		void UpdateContentView(float width);

		void ChangeSelectFolder(const std::string& path);
		void ChangeFolderFromStack();

	private:
		bool m_IsFirstOpen = true;
		ImGuiWindowFlags m_WindowFlags = 0;
		ImVec2 m_WindowSize;
		std::string m_SelectFolder = CONTENT_DIR;
		std::string m_SelectContent;

		bool m_ClickXButton1 = false;
		bool m_ClickXButton2 = false;
		std::stack<std::string> m_PriorSelectFolders;
		std::stack<std::string> m_NextSelectFolders;
	};

}


