#pragma once

#include "imgui.h"
#include "imgui_internal.h"

namespace PARS
{
	namespace IMGUIHELP
	{
		static ImVec4 GetImGuiWindowSize()
		{
			ImVec2 vMin = ImGui::GetWindowContentRegionMin();
			ImVec2 vMax = ImGui::GetWindowContentRegionMax();

			vMin.x += ImGui::GetWindowPos().x - ImGui::GetStyle().WindowPadding.x;
			vMin.y += ImGui::GetWindowPos().y - ImGui::GetStyle().WindowPadding.y;
			vMax.x += ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x;
			vMax.y += ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y;

			ImVec4 result(vMin.x, vMin.y, vMax.x - vMin.x, vMax.y - vMin.y);

			return result;
		}

		static ImVec4 GetImGuiItemSize()
		{
			ImVec2 vMin = ImGui::GetItemRectMin();
			ImVec2 vMax = ImGui::GetItemRectMax();

			ImVec4 result(vMin.x, vMin.y, vMax.x - vMin.x, vMax.y - vMin.y);

			return result;
		}

		static void DrawRectBox(const ImVec4& rect, ImU32 color = IM_COL32(255, 255, 50, 255))
		{
			ImGui::GetForegroundDrawList()->AddRect(
				{ rect.x, rect.y }, { rect.x + rect.z, rect.y + rect.w }, color);
		}

		static void DrawFilledRectBox(const ImVec4& rect, ImU32 color = IM_COL32(255, 255, 50, 50))
		{
			ImGui::GetForegroundDrawList()->AddRectFilled(
				{ rect.x, rect.y }, { rect.x + rect.z, rect.y + rect.w }, color);
		}

		static void CheckCurrentSelect(bool condition)
		{
			if (condition)
			{
				if(ImGui::IsWindowFocused())
					DrawFilledRectBox(GetImGuiItemSize());
				else
					DrawFilledRectBox(GetImGuiItemSize(), IM_COL32(240, 240, 240, 120));
					

			}
		}
	}
}
