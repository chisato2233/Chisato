workspace "Chisato"
	-- 版本
	architecture "x64"

	--配置
	configurations{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"
	--输出路径
	outputdir="%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	--包含目录
	IncludeDir={}
	IncludeDir["GLFW"]="Chisato/packages/GLFW/include"
	IncludeDir["spdlog"]="Chisato/packages/spdlog/include"
	IncludeDir["GLAD"]="Chisato/packages/GLAD/include"
	IncludeDir["Imgui"]="Chisato/packages/Imgui"
	IncludeDir["glm"]="Chisato/packages/glm"
	IncludeDir["stb"] ="Chisato/packages/stb"

	--引入GLFW的premake文件
	include "Chisato/packages/GLFW"
	include "Chisato/packages/GLAD"
	include "Chisato/packages/Imgui"
	include "Chisato/packages/glm"

	--工程：chisato
	project"Chisato"
		location "Chisato"
		kind "SharedLib"
		language "C++"

		--目标路径
		targetdir ("bin/".. outputdir .."/%{prj.name}")
		--链接路径
		objdir ("bin-int/".. outputdir .."/%{prj.name}")

		--预编译头
		pchheader "pch.h"
		pchsource "Chisato/src/pch.cpp"
		forceincludes{"pch.h"}

		files{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",

			"%{IncludeDir.stb}/**.cpp",
			"%{IncludeDir.stb}/**.h",
		}

		includedirs{
			"%{prj.name}/src",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.Imgui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb}",
		}
		
		links{
			"GLFW",
			"opengl32.lib",
			"dwmapi.lib",
			"imgui",
			"GLAD", 
		}

		-- windows版本
		filter"system:windows"
			cppdialect "C++20"
			staticruntime "On"
			systemversion "latest"

			defines{
				"CST_PLATFORM_WINDOWS",
				"CST_BUILD_DLL",
				"GLFW_INCLUDE_NONE",
				"IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
			}

			postbuildcommands{
				("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
			}
		
		-- Debug版本
		filter "configurations:Debug"
			defines {
				"CST_DEBUGS",
				"CST_ASSERT_ENABLE"
			}
			symbols "On"
			runtime "Debug"
			staticruntime "off"
			
		--Release版本	
		filter "configurations:Release"
			defines "CST_RELEASE"
			optimize "On"
			runtime "Release"
			staticruntime "off"	
		
		-- Dist版本	
		filter "configurations:Dist"
			defines "CST_DIST"
			optimize "On"
			staticruntime "off"

	
	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/".. outputdir .."/%{prj.name}")
		objdir ("bin-int/".. outputdir .."/%{prj.name}")

		--预编译头
		pchheader "pch.h"
		pchsource "%{prj.name}/src/pch.cpp"
		forceincludes{"pch.h"}
		
		files{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",

			"%{IncludeDir.stb}/**.cpp",
			"%{IncludeDir.stb}/**.h",

		}

		includedirs{
			"Chisato/src",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.Imgui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb}",
		}

		links{
			"Chisato",
		}

		filter"system:windows"
			cppdialect "C++20"
			
			systemversion "latest"

			defines{
				"CST_PLATFORM_WINDOWS",
				"GLFW_INCLUDE_NONE",
			}

		filter "configurations:Debug"
			defines "CST_DEBUGS"
			symbols "On"
			staticruntime "off"
			
		filter "configurations:Release"
			defines "CST_RELEASE"
			optimize "On"
			staticruntime "off"
			
		filter "configurations:Dist"
			defines "CST_DIST"
			optimize "On"
			staticruntime "off"