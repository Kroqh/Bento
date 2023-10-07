project "Bento-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Bento/vendor/spdlog/include",
		"%{wks.location}/Bento/src",
		"%{wks.location}/Bento/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Box2D}"
	}

	links
	{
		"Bento"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "BENTO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BENTO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BENTO_DIST"
		runtime "Release"
		optimize "on"