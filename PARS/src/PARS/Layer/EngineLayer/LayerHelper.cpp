#include "stdafx.h"
#include "PARS/Layer/EngineLayer/LayerHelper.h"

namespace PARS
{
	namespace IMGUIHELP
	{
		ImVec4 GetImGuiWindowSize()
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

		ImVec4 GetImGuiWindowBoxSize()
		{
			ImVec4 result = GetImGuiWindowSize();
			result.x += ImGui::GetStyle().WindowPadding.x + ImGui::GetStyle().FramePadding.x;
			result.y += ImGui::GetStyle().WindowPadding.y + ImGui::GetStyle().FramePadding.y;
			result.z -= ImGui::GetStyle().WindowPadding.x * 2;
			result.w -= ImGui::GetStyle().WindowPadding.y * 2;
			return result;
		}

		ImVec4 GetImGuiItemSize()
		{
			ImVec2 vMin = ImGui::GetItemRectMin();
			ImVec2 vMax = ImGui::GetItemRectMax();

			ImVec4 result(vMin.x, vMin.y, vMax.x - vMin.x, vMax.y - vMin.y);

			return result;
		}

		void DrawRectBox(const ImVec4& rect, ImU32 color)
		{
			ImGui::GetForegroundDrawList()->AddRect(
				{ rect.x, rect.y }, { rect.x + rect.z, rect.y + rect.w }, color);
		}

		void DrawFilledRectBox(const ImVec4& rect, ImU32 color)
		{
			ImGui::GetForegroundDrawList()->AddRectFilled(
				{ rect.x, rect.y }, { rect.x + rect.z, rect.y + rect.w }, color);
		}

		void CheckCurrentSelect(bool condition)
		{
			if (condition)
			{
				if (ImGui::IsWindowFocused())
					DrawFilledRectBox(GetImGuiItemSize());
				else
					DrawFilledRectBox(GetImGuiItemSize(), IM_COL32(240, 240, 240, 120));
			}
		}

		void ShowAssetPath(const std::string& path)
		{
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(path.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}

		void ShowItemInfo(const std::string& name, std::initializer_list<std::string>&& texts)
		{
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::BeginChild("Name", ImVec2(0, 20));
				ImGui::BulletText(name.c_str());
				ImGui::EndChild();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				for (const auto& text : texts)
					ImGui::TextUnformatted(text.c_str());
				ImGui::PopTextWrapPos();
			
				ImGui::EndTooltip();
			}
		}
	}
}

