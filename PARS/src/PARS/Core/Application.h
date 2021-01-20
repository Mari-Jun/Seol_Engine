#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	//forward declaration
	class Window;


	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		UPtr<Window> m_Window;
	};

	Application* CreateApplication();
}