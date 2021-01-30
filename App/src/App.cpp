#include <PARS.h>

class ExampleLayer : public PARS::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void Update() override
	{
		static int count = 0;
		if (++count == 100)
		{
			PARS_INFO("Kill");
			SetStateDead();
		}
	}
};

class App : public PARS::Application
{
public:
	App()
	{
		
	}

	bool Initialize() override
	{
		bool result = Application::Initialize();

		PARS_INFO("Hellof");

		AddLayer(PARS::CreateSPtr<ExampleLayer>());

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