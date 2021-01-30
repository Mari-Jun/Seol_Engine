#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	struct WindowInfo;
	class DirectX12;
	class ImGuiLayer;

	class Renderer
	{
	public:
		Renderer(const WindowInfo& info);
		virtual ~Renderer();
	
		bool Initialize();
		void ShutDown();
		void Draw();

	public:
		const SPtr<ImGuiLayer>& CreateImGui();

	private:
		WindowInfo m_WindowInfo;
		SPtr<DirectX12> m_DirectX12;
		SPtr<ImGuiLayer> m_ImGuiLayer;
	};
}



