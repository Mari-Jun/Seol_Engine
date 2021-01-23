#pragma once

extern PARS::Application* PARS::CreateApplication();

int main(int argc, char** argv)
{
	PARS::Log::Init();

	auto app = PARS::CreateApplication();
	if (!app->Initialize())
	{
		PARS_ERROR("Could not initialize Application");
	}
	else
	{
		PARS_INFO("Physics and Rendering Simulation");
		app->Run();
		app->ShutDown();
	}
	delete app;
}
