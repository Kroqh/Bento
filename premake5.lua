workspace " Bento"  
architecture "x64"
configurations { "Debug", "Release", "Dist" } 


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root foler (solution directory)
Includedir = {}
Includedir["GLFW"] = "Bento/vendor/GLFW/include"

include "Bento/vendor/GLFW"

project "Bento"  
    location "Bento"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 
     
    pchheader "Bentopch.h"
    pchsource "%{prj.name}/src/Bentopch.cpp"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" } 

    includedirs
    { 
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{Includedir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "BENTO_PLATFORM_WINDOWS", 
            "BENTO_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
 

    filter "configurations:Debug"
        defines "BENTO_DEBUG"   
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"  
        defines { "BENTO_RELEASE" }   
        buildoptions "/MD"  
        optimize "On" 

    filter "configurations:Dist"  
        defines { "BENTO_DIST" }   
        buildoptions "/MD"   
        optimize "On" 



project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}") 
     
    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" } 

    includedirs
    { 
        "Bento/vendor/spdlog/include",
        "Bento/src" 
    }

    links
    {
        "Bento"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "BENTO_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "BENTO_DEBUG"   
        buildoptions "/MDd"   
        symbols "On"

    filter "configurations:Release"  
        defines { "BENTO_RELEASE" }    
        buildoptions "/MD"   
        optimize "On" 

    filter "configurations:Dist"  
        defines { "BENTO_DIST" }  
        buildoptions "/MD"     
        optimize "On" 
