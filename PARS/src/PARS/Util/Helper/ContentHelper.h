#pragma once

namespace PARS
{
	using Contents = std::vector<std::filesystem::directory_entry>;

	class ContentHelper
	{
	public:
		inline static void ReloadContents()
		{
			GetDirectorys(CONTENT_DIR);
			SetContents(s_StaticMeshContents, { ".obj" }, {});
		}

		inline static Contents GetContentsInDirectory(const std::string& directory,
			const std::initializer_list<std::string>& filter, const std::initializer_list<std::string>& antiFilter)
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

		template<typename ... Args>
		inline static void ShowItemInfo(std::initializer_list<std::string>&& texts)
		{
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				for(const auto& text : texts)
					ImGui::TextUnformatted(text.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}

		inline static std::string GetFileNameFromPath(std::string path)
		{
			path = path.substr(path.rfind('\\') + 1);
			path = path.substr(0, path.rfind('.'));
			return path;
		}

		inline static Contents GetStaticMeshContents() { return s_StaticMeshContents; }

	private:
		inline static void GetDirectorys(const std::filesystem::path& path)
		{
			for (const auto& file : std::filesystem::directory_iterator(path))
			{
				if (file.is_directory())
				{
					std::string dirPath = file.path().relative_path().u8string();
					GetDirectorys(dirPath);
					s_DirectoryPaths.emplace_back(std::move(dirPath));
				}
			}
		}

		inline static void SetContents(Contents& contents, const std::initializer_list<std::string>& filter, const std::initializer_list<std::string>& antiFilter)
		{
			for (const auto& path : s_DirectoryPaths)
			{
				Contents result = GetContentsInDirectory(path, filter, antiFilter);
				contents.insert(contents.end(), result.begin(), result.end());
			}
		}

	private:
		static std::vector<std::string> s_DirectoryPaths;
		static Contents s_StaticMeshContents;
	};
}


