#include "stdafx.h"
#include "PARS/Util/Content/AssetStore.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	AssetStore* AssetStore::s_Instance = nullptr;

	AssetStore::AssetStore()
	{
		s_Instance = this;

		m_GraphicsAssetStore = CreateUPtr<GraphicsAssetStore>();
		m_GraphicsAssetStore->Initialize();

		ReloadContents();
	}

	void AssetStore::Shutdown()
	{
		m_GraphicsAssetStore->Shutdown();
	}

	void AssetStore::Update()
	{
	}

	void AssetStore::ReloadContents()
	{
		GetDirectorys(CONTENT_DIR);

		GetContents(m_MaterialContents, { ".mtl" }, {});
		for (const auto& file : m_MaterialContents)
		{
			m_GraphicsAssetStore->LoadMaterial(GetPathFromFile(file), GetParentPathFromFile(file), GetExtentionFromFile(file));
		}

		GetContents(m_StaticMeshContents, { ".obj" }, {});

		for (const auto& file : m_StaticMeshContents)
		{
			m_GraphicsAssetStore->LoadMesh(GetPathFromFile(file), GetParentPathFromFile(file), GetExtentionFromFile(file));
		}
	}

	Contents AssetStore::GetContentsInDirectory(const std::string& directory, const std::initializer_list<std::string>& filter, const std::initializer_list<std::string>& antiFilter)
	{
		std::vector<std::filesystem::directory_entry> files;

		for (const auto& file : std::filesystem::directory_iterator(directory))
		{
			if (!file.is_directory() && !file.is_regular_file())
				continue;

			std::string extension = file.path().extension().u8string();
			if (filter.size() != 0 && filter.end() == std::find(filter.begin(), filter.end(), extension))
				continue;
			if (antiFilter.size() != 0 && antiFilter.end() != std::find(antiFilter.begin(), antiFilter.end(), extension))
				continue;

			files.push_back(file);
		}

		sort(files.begin(), files.end());

		return files;
	}

	void AssetStore::ShowItemInfo(std::initializer_list<std::string>&& texts)
	{
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			for (const auto& text : texts)
				ImGui::TextUnformatted(text.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
	std::string AssetStore::GetPathFromFile(const std::filesystem::directory_entry& file)
	{
		return file.path().relative_path().u8string();
	}

	std::string AssetStore::GetParentPathFromFile(const std::filesystem::directory_entry& file)
	{
		return file.path().parent_path().u8string();
	}

	std::string AssetStore::GetStemFromFile(const std::filesystem::directory_entry& file)
	{
		return file.path().stem().u8string();
	}

	std::string AssetStore::GetPathNotExtentionFromFile(const std::filesystem::directory_entry& file)
	{
		std::string path = GetPathFromFile(file);
		std::string extention = GetExtentionFromFile(file);
		return path.substr(0, path.size() - extention.size());
	}

	std::string AssetStore::GetExtentionFromFile(const std::filesystem::directory_entry& file)
	{
		return file.path().extension().u8string();
	}

	std::string AssetStore::GetFileNameFromPath(std::string path)
	{
		path = path.substr(path.rfind('\\') + 1);
		path = path.substr(0, path.rfind('.'));
		return path;
	}

	void AssetStore::GetDirectorys(const std::filesystem::path& path)
	{
		for (const auto& file : std::filesystem::directory_iterator(path))
		{
			if (file.is_directory())
			{
				std::string dirPath = file.path().relative_path().u8string();
				GetDirectorys(dirPath);
				m_DirectoryPaths.emplace_back(std::move(dirPath));
			}
		}
	}

	void AssetStore::GetContents(Contents& contents, const std::initializer_list<std::string>& filter, const std::initializer_list<std::string>& antiFilter)
	{
		for (const auto& path : m_DirectoryPaths)
		{
			Contents result = GetContentsInDirectory(path, filter, antiFilter);
			contents.insert(contents.end(), result.begin(), result.end());
		}
	}
}
