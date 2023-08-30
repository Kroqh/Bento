workspace " Bento"  
architecture "x64"
configurations { "Debug", "Release", "Dist" } 
startproject "Bento-Editor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root foler (solution directory)
Includedir = {}
Includedir["GLFW"] = "Bento/vendor/GLFW/include"
Includedir["Glad"] = "Bento/vendor/Glad/include"
Includedir["ImGui"] = "Bento/vendor/imgui"
Includedir["glm"] = "Bento/vendor/glm"
Includedir["stb_image"] = "Bento/vendor/stb_image"
Includedir["entt"] = "Bento/vendor/entt/include"
Includedir["yaml_cpp"] = "Bento/vendor/yaml-cpp/include"
Includedir["ImGuizmo"] = "Bento/vendor/ImGuizmo"

include "Bento/vendor/GLFW"
include "Bento/vendor/Glad"
include "Bento/vendor/imgui"
include "Bento/vendor/yaml-cpp"

project "Bento"  
    location "Bento"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 
     
    pchheader "Bentopch.h"
    pchsource "%{prj.name}/src/Bentopch.cpp"

    files { "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",

        "%{prj.name}/vendor/ImGuizmo/**.h",
        "%{prj.name}/vendor/ImGuizmo/**.cpp"
    } 

    includedirs
    { 
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{Includedir.GLFW}",
        "%{Includedir.Glad}",
        "%{Includedir.ImGui}",
        "%{Includedir.glm}",
        "%{Includedir.stb_image}",
        "%{Includedir.entt}",
        "%{Includedir.yaml_cpp}",
        "%{Includedir.ImGuizmo}"

    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "yaml-cpp",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "files:Bento/vendor/ImGuizmo/**.cpp"
	    flags { "NoPCH" }

    filter "system:windows"
    
        systemversion "latest"

        defines 
        {
            "BENTO_PLATFORM_WINDOWS", 
            "BENTO_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_CRT_SECURE_NO_WARNINGS",
            "YAML_CPP_STATIC_DEFINE"
            
        }
 

    filter "configurations:Debug"
        defines "BENTO_DEBUG"   
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"  
        defines { "BENTO_RELEASE" }   
        buildoptions "/MD"  
        optimize "on" 

    filter "configurations:Dist"  
        defines { "BENTO_DIST" }   
        buildoptions "/MD"   
        optimize "on" 



project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 
     
    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" } 

    includedirs
    { 
        "Bento/vendor/spdlog/include",
        "Bento/src",
        "Bento/vendor",
        "%{Includedir.glm}",
        "%{Includedir.entt}",
        "%{Includedir.ImGuizmo}"
    }

    links
    {
        "Bento"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "BENTO_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "BENTO_DEBUG"   
        buildoptions "/MDd"   
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"  
        defines { "BENTO_RELEASE" }    
        buildoptions "/MD"   
        runtime "Release"
        optimize "On" 

    filter "configurations:Dist"  
        defines { "BENTO_DIST" }  
        buildoptions "/MD"  
        runtime "Release"   
        optimize "On" 


project "Bento-Editor"
    location "Bento-Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 
     
    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" } 

    includedirs
    { 
        "Bento/vendor/spdlog/include",
        "Bento/src",
        "Bento/vendor",
        "%{Includedir.glm}",
        "%{Includedir.entt}",
        "%{Includedir.ImGuizmo}"
    }

    links
    {
        "Bento"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "BENTO_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "BENTO_DEBUG"   
        buildoptions "/MDd"   
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"  
        defines { "BENTO_RELEASE" }    
        buildoptions "/MD"   
        runtime "Release"
        optimize "On" 

    filter "configurations:Dist"  
        defines { "BENTO_DIST" }  
        buildoptions "/MD"  
        runtime "Release"   
        optimize "On" 



