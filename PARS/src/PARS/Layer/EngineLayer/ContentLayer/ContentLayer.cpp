#include "stdafx.h"
#include "PARS/Layer/EngineLayer/LayerHelper.h"
#include "PARS/Layer/EngineLayer/ContentLayer/ContentLayer.h"
#include "PARS/Input/Input.h"
#include "PARS/Util/Content/AssetStore.h"
#include "PARS/Component/Render/Texture/Texture.h"

namespace PARS
{
	ContentLayer::ContentLayer(const std::string& name)
		: Layer(name)
	{
	}

	void ContentLayer::Initialize()
	{
	}

	void ContentLayer::Shutdown()
	{
	}

	void ContentLayer::LayerInput()
	{
		m_ClickXButton1 = Input::IsKeyFirstPressed(PARS_MOUSE_XBUTTON1);
		m_ClickXButton2 = Input::IsKeyFirstPressed(PARS_MOUSE_XBUTTON2);
	}

	void ContentLayer::Update()
	{
		ImGui::SetNextWindowSize(ImVec2(1000, 300), ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Content Layer", nullptr, m_WindowFlags))
		{
			ChangeFolderFromStack();

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
				ImVec4 rect = IMGUIHELP::GetImGuiWindowSize();
				UpdateContentView(rect.z);
			}
			ImGui::EndChild();		

		
		}
		m_WindowSize = ImGui::GetItemRectSize();

		ImGui::End();
	}

	void ContentLayer::UpdateFolderList()
	{		
		ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow |
			ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_FramePadding |
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen;

		if (ImGui::TreeNodeEx("Content", treeFlags))
		{
			if (ImGui::IsItemClicked())
				ChangeSelectFolder(CONTENT_DIR);
			IMGUIHELP::CheckCurrentSelect(CONTENT_DIR == m_SelectFolder);

			RecursiveFolderList(CONTENT_DIR);
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Levels", treeFlags))
		{
			if (ImGui::IsItemClicked())
				ChangeSelectFolder(LEVEL_DIR);
			IMGUIHELP::CheckCurrentSelect(LEVEL_DIR == m_SelectFolder);

			RecursiveFolderList(LEVEL_DIR);
			ImGui::TreePop();
		}
	}

	void ContentLayer::RecursiveFolderList(const std::filesystem::path& path)
	{
		 ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow |
			ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_FramePadding |
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Selected;

		for (const auto& file : std::filesystem::directory_iterator(path))
		{
			if (file.is_directory())
			{
				std::string name = file.path().filename().u8string();
				std::string dirPath = file.path().relative_path().u8string();
				
				if (dirPath == m_SelectFolder.substr(0, dirPath.size()) && dirPath != m_SelectFolder)
					ImGui::SetNextItemOpen(true);

				if (ImGui::TreeNodeEx(name.c_str(), treeFlags))
				{
					if (ImGui::IsItemClicked())
						ChangeSelectFolder(dirPath);
					IMGUIHELP::CheckCurrentSelect(dirPath == m_SelectFolder);

					RecursiveFolderList(dirPath);
					ImGui::TreePop();
				}
				else
				{
					if (ImGui::IsItemClicked())
						ChangeSelectFolder(dirPath);
					IMGUIHELP::CheckCurrentSelect(dirPath == m_SelectFolder);
				}
			}
		}
	}

	void ContentLayer::UpdateContentView(float width)
	{
		static std::vector<std::filesystem::directory_entry> folders;

		static std::set<SPtr<Asset>, AssetCompare> assets;

		if (m_IsUpdateContentView)
		{
			m_IsUpdateContentView = false;

			folders = AssetStore::GetAssetStore()->GetFolderInDirectory(m_SelectFolder);
			assets = AssetStore::GetAssetStore()->GetAssetsOfDirectory(m_SelectFolder);
		}

		const auto& folderTex = AssetStore::GetAssetStore()->GetTexture(ENGINE_CONTENT_DIR + "/Texture\\folder");
		const auto& meshTex = AssetStore::GetAssetStore()->GetTexture(ENGINE_CONTENT_DIR + "/Texture\\mesh");
		const auto& materialTex = AssetStore::GetAssetStore()->GetTexture(ENGINE_CONTENT_DIR + "/Texture\\material");
		const auto& textureTex = AssetStore::GetAssetStore()->GetTexture(ENGINE_CONTENT_DIR + "/Texture\\texture");
		const auto& levelTex = AssetStore::GetAssetStore()->GetTexture(ENGINE_CONTENT_DIR + "/Texture\\level");
		
		width -= ImGui::GetStyle().WindowPadding.x * 2 + ImGui::GetStyle().FramePadding.x * 2;

		float cWidth = 120.0f;
		int line = ((int)(width / cWidth));
		cWidth = (width - ((line- 1) * ImGui::GetStyle().ItemSpacing.x * 2)) / line;

		int cnt = 0;

		if (line > 0)
		{
			for (const auto& folder : folders)
			{
				std::string stemName = folder.path().stem().u8string();
				std::string path = folder.path().relative_path().string();

				ImGui::BeginGroup();
				if (folderTex != nullptr && folderTex->GetResource() != nullptr)
				{
					ImGui::ImageButton((ImTextureID)folderTex->GetGpuHandle().ptr, ImVec2((float)cWidth, (float)cWidth * 0.9f));
					if (ImGui::IsItemHovered())
					{
						IMGUIHELP::ShowItemInfo(stemName, { path });
						if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
							ChangeSelectFolder(path);
					}
				}
				ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + cWidth);
				ImGui::Text(stemName.c_str());
				ImGui::PopTextWrapPos();

				ImGui::EndGroup();

				if (++cnt % line != 0)
				{
					ImGui::SameLine();
				}
			}

			for (const auto& asset : assets)
			{
				ImGui::BeginGroup();

				switch (HashCode(asset->GetExtension().c_str()))
				{
				case HashCode(".obj"):
					if (meshTex != nullptr && meshTex->GetResource() != nullptr)
					{
						ImGui::ImageButton((ImTextureID)meshTex->GetGpuHandle().ptr, ImVec2((float)cWidth, (float)cWidth * 0.9f));
						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
						{
							//ChangeSelectFolder(path);
						}
					} break;
				case HashCode(".mtl"):
					if (materialTex != nullptr && materialTex->GetResource() != nullptr)
					{
						ImGui::ImageButton((ImTextureID)materialTex->GetGpuHandle().ptr, ImVec2((float)cWidth, (float)cWidth * 0.9f));
						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
						{
							asset->OpenEditLayer();
						}
					} break;
				case HashCode(".dds"):
					if (textureTex != nullptr && textureTex->GetResource() != nullptr)
					{
						ImGui::ImageButton((ImTextureID)textureTex->GetGpuHandle().ptr, ImVec2((float)cWidth, (float)cWidth * 0.9f));
						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
						{
							//ChangeSelectFolder(path);
						}
					} break;
				case HashCode(".lvl"):
					if (levelTex != nullptr && levelTex->GetResource() != nullptr)
					{
						ImGui::ImageButton((ImTextureID)levelTex->GetGpuHandle().ptr, ImVec2((float)cWidth, (float)cWidth * 0.9f));
						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
						{
							LoadLevel(AssetStore::GetAssetStore()->GetLevel(asset->GetFilePath()));
						}
					} break;
					break;
				default:
					break;
				}

				ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + cWidth);
				ImGui::Text(asset->GetName().c_str());
				ImGui::PopTextWrapPos();

				ImGui::EndGroup();

				if (++cnt % line != 0)
				{
					ImGui::SameLine();
				}
			}
		}
	}

	void ContentLayer::ChangeSelectFolder(std::string path)
	{
		std::replace_if(path.begin(), path.end(), [](char text) {
			return text == '\\';
			}, '/');
		if (m_SelectFolder != path)
		{
			while (!m_NextSelectFolders.empty())
				m_NextSelectFolders.pop();
			m_PriorSelectFolders.push(m_SelectFolder);
			m_SelectFolder = path;
			m_IsUpdateContentView = true;
		}
	}

	void ContentLayer::ChangeFolderFromStack()
	{
		ImVec4 rect = IMGUIHELP::GetImGuiWindowSize();
		if (ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows |
			ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
		{
			if (m_ClickXButton1 && !m_PriorSelectFolders.empty())
			{
				m_NextSelectFolders.push(m_SelectFolder);
				m_SelectFolder = m_PriorSelectFolders.top();
				m_PriorSelectFolders.pop();
				m_IsUpdateContentView = true;
			}
			else if (m_ClickXButton2 && !m_NextSelectFolders.empty())
			{
				m_PriorSelectFolders.push(m_SelectFolder);
				m_SelectFolder = m_NextSelectFolders.top();
				m_NextSelectFolders.pop();
				m_IsUpdateContentView = true;
			}
			IMGUIHELP::DrawRectBox(rect);
		}
	}
}
