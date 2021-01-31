#include <PARS.h>

class SimulationApp : public PARS::Application
{
public:
	SimulationApp()
	{
		
	}

	bool Initialize() override
	{
		bool result = Application::Initialize();

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