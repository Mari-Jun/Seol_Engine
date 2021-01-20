workspace "Physics_And_Rendering_Simulation"
	architecture "x64"
	startproject "App"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group ""

include "PARS"
include "App"