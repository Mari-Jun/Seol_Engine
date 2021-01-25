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
		void ProcessInput();
		void Update();
		void Draw();

	private:
		bool m_Running;
		UPtr<Window> m_Window;
		UPtr<Timer> m_Timer;
		UPtr<Renderer> m_Renderer;
	};

	Application* CreateApplication();
}