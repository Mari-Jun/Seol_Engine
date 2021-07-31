#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	//forward declaration
	class Window;
	class Timer;
	class LevelManager;
	class LayerManager;
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
		void OpenLevel(const SPtr<class Level>& level);
		void AddLayer(const SPtr<class Layer>& layer);

	private:
		void ProcessInput();
		void Update();
		void Draw();

	private:
		bool m_Running;
		UPtr<Window> m_Window;
		UPtr<Timer> m_Timer;
		UPtr<LevelManager> m_LevelManager;
		UPtr<LayerManager> m_LayerManager;
		UPtr<Renderer> m_Renderer;
	};

	Application* CreateApplication();
}