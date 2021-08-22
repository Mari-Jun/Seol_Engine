#include "stdafx.h"
#include "PARS/Layer/EngineLayer/ContentLayer/ContentLayer.h"
#include "PARS/Util/Helper/ContentHelper.h"

namespace PARS
{
	ContentLayer::ContentLayer(const std::string& name)
		: Layer(name)
	{
	}

	void ContentLayer::Initialize()
	{
		ContentHelper::ReloadContents();
	}

	void ContentLayer::Shutdown()
	{
	}

	void ContentLayer::Update()
	{
		ImGui::SetNextWindowSize(ImVec2(1000, 300), ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Content Layer", nullptr, m_WindowFlags))
		{
			ImGui::Columns(2, "Content");
			if (m_IsFirstOpen)
			{
				ImGui::SetColumnWidth(0, ImGui::GetWindowSize().x * 0.2f);
				m_IsFirstOpen = false;
			}
			float size = ImGui::GetColumnWidth(0);
			if (ImGui::BeginChild("Folder List", ImVec2(size - 20.0f, 0), true))
			{
				UpdateFolderList();
			}
			ImGui::EndChild();

			ImGui::NextColumn();

			size = ImGui::GetColumnWidth(1);
			if (ImGui::BeginChild("Content View", ImVec2(size - 20.0f, 0), true))
			{
				UpdateContentView(size);
			}
			ImGui::EndChild();		
		}
		m_WindowSize = ImGui::GetItemRectSize();
		ImGui::End();

		m_IsUpdateContentView = false;
	}

	void ContentLayer::UpdateFolderList()
	{		
		if (ImGui::CollapsingHeader("Content"))
		{
			std::string select = RecursiveFolderList(CONTENT_DIR);
			if (!select.empty())
			{
				m_SelectFolder = select;
				m_IsUpdateContentView = true;
			}
		}
	}

	std::string ContentLayer::RecursiveFolderList(const std::filesystem::path& path)
	{
		std::string select;
		for (const auto& file : std::filesystem::directory_iterator(path))
		{
			if (file.is_directory())
			{
				std::string name = file.path().filename().u8string();
				std::string dirPath = file.path().relative_path().u8string();
				if (ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick))
				{
					select = RecursiveFolderList(dirPath);
					ImGui::TreePop();
				}
				if (ImGui::IsItemClicked() && select.empty())
				{
					select = dirPath;
				}
			}
		}
		return select;
	}

	void ContentLayer::UpdateContentView(float width)
	{
		static std::vector<std::filesystem::directory_entry> files;

		if (m_IsUpdateContentView)
		{
			files = ContentHelper::GetContentsInDirectory(m_SelectFolder, {}, { ".mtl" });
		}

		int cnt = 0;

		for (const auto& file : files)
		{
			std::string stemName = file.path().stem().u8string();
			std::string fileName = file.path().filename().u8string();
			ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
			if (ImGui::Selectable(stemName.c_str(), m_SelectContent == fileName, ImGuiSelectableFlags_None, ImVec2(width / 8, m_WindowSize.y / 3)))
			{
				m_SelectContent = fileName;
			}
			ImGui::PopStyleVar();
			
			if (++cnt % 7 != 0)
			{
				ImGui::SameLine();
			}
		}
	}
}
