project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs{

		"include"

	}

	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "system:macosx"
		pic "On"

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		staticruntime "on"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		staticruntime "on"	
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		staticruntime "on"
		runtime "Release"
		optimize "on"
        symbols "off"