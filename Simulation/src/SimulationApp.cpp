#include <PARS.h>
#include "PARS/Core/EntryPoint.h"
#include "EditorLevel.h"
#include "EditorLayer.h"

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
		AddLayer(PARS::CreateSPtr<PARS::DetailLayer>());	

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