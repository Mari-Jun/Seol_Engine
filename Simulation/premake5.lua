project "Simulation"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/PARS/vendor/spdlog/include",
		"%{wks.location}/PARS/vendor/imgui",
		"%{wks.location}/PARS/vendor/d3d12_Helper/include/directx",
		"%{wks.location}/PARS/src",
		"%{wks.location}/PARS/vendor",
		"%{wks.location}/Simulation/src"
	}
	
	links
	{
		"PARS"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "PARS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PARS_RELEASE"
		symbols "On"