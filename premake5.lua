workspace "Chisato"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}


outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project"Chisato"
	location "Chisato"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/".. outputdir .."/%{prj.name}")
	objdir ("bin-int/".. outputdir .."/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/packages/spdlog/include"
	}

	filter"system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines{
			"CST_PLATFORM_WINDOWS",
			"CST_BUILD_DLL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CST_DEBUGS"
		symbols "On"
		
	filter "configurations:Release"
		defines "CST_RELEASE"
		optimize "On"	
		
	filter "configurations:Dist"
		defines "CST_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/".. outputdir .."/%{prj.name}")
	objdir ("bin-int/".. outputdir .."/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Chisato/packages/spdlog/include",
		"Chisato/src"
	}

	links{
		"Chisato"
	}

	filter"system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines{
			"CST_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CST_DEBUGS"
		symbols "On"
		
	filter "configurations:Release"
		defines "CST_RELEASE"
		optimize "On"	
		
	filter "configurations:Dist"
		defines "CST_DIST"
		optimize "On"