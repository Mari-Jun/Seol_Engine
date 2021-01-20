#pragma once

extern PARS::Application* PARS::CreateApplication();

int main(int argc, char** argv)
{
	PARS::Log::Init();
	PARS_CORE_INFO("Physics and Rendering Simulation");

	auto app = PARS::CreateApplication();
	app->Run();
	delete app;
}
