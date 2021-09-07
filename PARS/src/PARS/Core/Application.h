#pragma once

#include "PARS/Core/Core.h"

namespace PARS
{
	//forward declaration
	class Window;
	class Timer;
	class LevelManager;
	class LayerManager;
	class AssetStore;
	class Renderer;

	enum class AppState
	{
		Active, Paused, Dead
	};

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
		static AppState s_AppState;
		UPtr<Window> m_Window;
		UPtr<Timer> m_Timer;
		UPtr<LevelManager> m_LevelManager;
		UPtr<LayerManager> m_LayerManager;
		UPtr<AssetStore> m_AssetStore;
		UPtr<Renderer> m_Renderer;

	public:
		inline static AppState GetAppState() { return s_AppState; }
		inline static void SetAppState(AppState state) { s_AppState = state; }
	};

	Application* CreateApplication();
}