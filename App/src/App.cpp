#include <PARS.h>

class App : public PARS::Application
{
public:
	App()
	{

	}
	
	~App()
	{

	}
};

PARS::Application* PARS::CreateApplication()
{
	return new App();
}