#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	class DirectX12;
	class ImGuiLayer;

	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();
	
		bool Initialize();
		void ShutDown();
		void Draw();

	public:
		const SPtr<ImGuiLayer>& CreateImGui();

	private:
		SPtr<DirectX12> m_DirectX12;
		SPtr<ImGuiLayer> m_ImGuiLayer;
	};
}



