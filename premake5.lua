include "vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Bento"
	architecture "x86_64"
	startproject "Bento-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	include "Bento/vendor/GLFW"
	include "Bento/vendor/Box2D"
	include "Bento/vendor/Glad"
	include "Bento/vendor/imgui"
	include "Bento/vendor/yaml-cpp"
group ""

group "Core"
	include "Bento"
	include "Bento-ScriptCore"
group ""

group "Tools"
include "Bento-Editor"
group ""

group "misc"
include "Sandbox"
group ""