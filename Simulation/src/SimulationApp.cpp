#include <PARS.h>
#include "PARS/Core/EntryPoint.h"
#include "EditorLevel.h"

class SimulationApp : public PARS::Application
{
public:
	SimulationApp()
	{
		
	}

	bool Initialize() override
	{
		bool result = Application::Initialize();

		AddLevel(PARS::CreateSPtr<PARS::EditorLevel>());

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