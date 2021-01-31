workspace "Physics_And_Rendering_Simulation"
	architecture "x64"
	startproject "App"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["ImGui"] = "%{wks.location}/PARS/vendor/imgui"

group "Dependencies"
	include "PARS/vendor/imgui"
group ""

include "PARS"
include "App"