#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	struct WindowInfo;
	class DirectX12;

	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();
	
		bool Initialize(const WindowInfo& info);
		void ShutDown();
		void Run();

	private:
		bool Draw();

	private:
		UPtr<DirectX12> m_DirectX12;
	};
}



