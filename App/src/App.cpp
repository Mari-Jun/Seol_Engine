#include <PARS.h>

class App : public PARS::Application
{
public:
	App()
	{
		
	}

	bool Initialize() override
	{
		bool result = Application::Initialize();

		return result;
	}
	
	~App()
	{

	}
};

PARS::Application* PARS::CreateApplication()
{
	return new App();
}