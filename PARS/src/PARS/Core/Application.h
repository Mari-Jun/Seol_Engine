#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	//forward declaration
	class Window;
	class Timer;
	class LayerManager;
	class Layer;
	class Renderer;

	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual bool Initialize();
		void ShutDown();
		void Run();

	public:
		void AddLayer(const SPtr<Layer>& layer);

	private:
		void ProcessInput();
		void Update();
		void Draw();

	private:
		bool m_Running;
		UPtr<Window> m_Window;
		UPtr<Timer> m_Timer;
		UPtr<LayerManager> m_LayerManager;
		UPtr<Renderer> m_Renderer;
	};

	Application* CreateApplication();
}