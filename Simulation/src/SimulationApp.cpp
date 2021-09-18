#include <PARS.h>
#include "PARS/Core/EntryPoint.h"
#include "PARS/Layer/EngineLayer/DockLayer/DockLayer.h"
#include "EditorLayer.h"
#include "PARS/Layer/EngineLayer/ObjectLayer/ObjectLayer.h"
#include "PARS/Layer/EngineLayer/ContentLayer/ContentLayer.h"
#include "PARS/Layer/EngineLayer/ViewportLayer/ViewportLayer.h"

class SimulationApp : public PARS::Application
{
public:
	SimulationApp()
	{
		
	}

	bool Initialize() override
	{
		bool result = Application::Initialize();

		AddLayer(PARS::CreateSPtr<PARS::DockLayer>());
		AddLayer(PARS::CreateSPtr<PARS::EditorLayer>());
		AddLayer(PARS::CreateSPtr<PARS::ContentLayer>());
		AddLayer(PARS::CreateSPtr<PARS::ObjectLayer>());
		AddLayer(PARS::CreateSPtr<PARS::LevelDetailLayer>());	
		AddLayer(PARS::CreateSPtr<PARS::ActorDetailLayer>());	
		AddLayer(PARS::CreateSPtr<PARS::ViewportLayer>());

		return result;
	}
	
	~SimulationApp()
	{

	}
};

PARS::Application* PARS::CreateApplication()
{
	return new SimulationApp();
}