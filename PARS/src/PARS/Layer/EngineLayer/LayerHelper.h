#pragma once

#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	namespace IMGUIHELP
	{
		ImVec4 GetImGuiWindowSize();
		ImVec4 GetImGuiWindowBoxSize();
		ImVec4 GetImGuiItemSize();
		void DrawRectBox(const ImVec4& rect, ImU32 color = IM_COL32(255, 255, 50, 255));
		void DrawFilledRectBox(const ImVec4& rect, ImU32 color = IM_COL32(255, 255, 50, 50));
		void CheckCurrentSelect(bool condition);
		void ShowAssetPath(const std::string& path);
		void ShowItemInfo(const std::string& name, std::initializer_list<std::string>&& texts);
	}
}
