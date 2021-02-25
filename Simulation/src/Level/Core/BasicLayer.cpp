#include "BasicLayer.h"

namespace PARS
{
	BasicLayer::BasicLayer(const std::string& name)
		: Layer(name)
	{
		m_WindowFlags =
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		ResizeLayer();
	}

	void BasicLayer::Update()
	{
		ImGui::SetNextWindowPos(m_WindowPos);
		ImGui::SetNextWindowSize(m_WindowSize);

		ImGui::Begin(m_LayerName.c_str(), false, m_WindowFlags);

		{
			static ImGuiWindowFlags objectsFlags = ImGuiWindowFlags_NoScrollbar;
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::BeginChild("ObjectsChild", ImVec2(m_WindowSize.x - 20.0f, m_WindowSize.y * 0.26f), true, objectsFlags);
			if (ImGui::BeginTabBar("Objects Tab"))
			{
				if (ImGui::BeginTabItem("Objects"))
				{
					UpdateObjects();
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();
		}

		{
			static ImGuiWindowFlags detailFlags = ImGuiWindowFlags_NoScrollbar;
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::BeginChild("DetailChild", ImVec2(m_WindowSize.x - 20.0f, m_WindowSize.y * 0.65f), true, detailFlags);
			if (ImGui::BeginTabBar("Detail Tab"))
			{
				if (ImGui::BeginTabItem("Detail"))
				{
					UpdateDetail();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Level Setting"))
				{
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();
		}

		{
			static ImGuiWindowFlags menuFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::BeginChild("Menu Child", ImVec2(m_WindowSize.x - 20.0f, m_WindowSize.y * 0.04f), true, menuFlags);
			UpdateEndMenu();
			ImGui::EndChild();
			ImGui::PopStyleVar();
		}

		ImGui::End();
		
	

		if (!m_IsOpen)
		{
			Destroy();
		}
	}

	void BasicLayer::Shutdown()
	{
		Renderer::SetClearColor(COLOR::Gray);
		f_Destroy();
	}

	void BasicLayer::ResizeLayer()
	{
		RECT rect;
		GetWindowRect(Window::GetWindowInfo()->m_hwnd, &rect);

		m_WindowSize = ImVec2(static_cast<float>(Window::GetWindowInfo()->m_LayerWidth), static_cast<float>(Window::GetWindowInfo()->m_Height));

		float x = rect.right - m_WindowSize.x - 7.5f;
		float y = rect.top + static_cast<float>(GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));

		m_WindowPos = ImVec2(x, y);
	}

	void BasicLayer::UpdateObjects()
	{
		for (const auto& object : m_ObjectNames)
		{
			if (ImGui::Selectable(object.c_str(), m_SelectObject == object))
			{
				m_SelectObject = object;
			}
		}
	}

	void BasicLayer::UpdateDetail()
	{
		const auto& iter = f_DetailFunctions.find(m_SelectObject);
		if (iter != f_DetailFunctions.cend())
		{
			for (const auto& treeNode : iter->second)
			{
				if (ImGui::TreeNode(treeNode.first.c_str()))
				{
					ImGui::BeginChild(treeNode.first.c_str(), ImVec2(ImGui::GetWindowWidth() * 0.9f, ImGui::GetWindowHeight() * 0.5f), true);

					treeNode.second();

					ImGui::EndChild();
					ImGui::TreePop();
				}
			}
		}
	}

	void BasicLayer::UpdateEndMenu()
	{
		if (ImGui::Button("Reset Level", ImVec2(180, ImGui::GetWindowHeight() * 0.6f)))
		{

		}
		ImGui::SameLine();
		if (ImGui::Button("Return To Menu", ImVec2(180, ImGui::GetWindowHeight() * 0.6f)))
		{
			m_IsOpen = false;
		}
	}

	void BasicLayer::AddObjectToLayer(std::string&& name)
	{
		m_ObjectNames.emplace_back(std::move(name));
	}

	void BasicLayer::AddDetailFunction(std::string&& objectName, std::string&& triName, const std::function<void()>& function)
	{
		auto iter = f_DetailFunctions.emplace(std::move(objectName), NodeFunction{ {triName, function} });
		if (!iter.second)
		{
			iter.first->second.emplace_back(triName, function);
		}
	}
}