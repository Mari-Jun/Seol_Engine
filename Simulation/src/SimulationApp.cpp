#include <PARS.h>
#include "PARS/Core/EntryPoint.h"
#include "EditorLevel.h"
#include "EditorLayer.h"
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

		//OpenLevel(PARS::CreateSPtr<PARS::EditorLevel>());
		AddLayer(PARS::CreateSPtr<PARS::EditorLayer>());
		AddLayer(PARS::CreateSPtr<PARS::ContentLayer>());
		AddLayer(PARS::CreateSPtr<PARS::DetailLayer>());	
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