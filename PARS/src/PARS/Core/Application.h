#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	//forward declaration
	class Window;
	class Timer;
	class Renderer;


	class Application
	{
	public:
		Application();
		virtual ~Application();

		bool Initialize();
		void ShutDown();
		void Run();

	private:
		UPtr<Window> m_Window;
		UPtr<Timer> m_Timer;
		UPtr<Renderer> m_Renderer;
	};

	Application* CreateApplication();
}