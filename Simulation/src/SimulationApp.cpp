#include <PARS.h>
#include "PARS/Core/EntryPoint.h"
#include "EditorLayer.h"
#include "Level0/ClearColor/ClearColorLevel.h"

class SimulationApp : public PARS::Application
{
public:
	SimulationApp()
	{
		
	}

	bool Initialize() override
	{
		bool result = Application::Initialize();

		AddLayer(PARS::CreateSPtr<PARS::EditorLayer>());

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