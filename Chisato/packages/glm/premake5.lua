project "gml"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"glm/**.hpp",
		"glm/**.inl",
	}


	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		staticruntime "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		staticruntime "on"
		optimize "speed"
		
    filter "configurations:Dist"
		runtime "Release"
		optimize "speed"
        symbols "off"
