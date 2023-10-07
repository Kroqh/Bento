
-- Bento Dependencies

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Bento/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Bento/vendor/yaml-cpp/include"
IncludeDir["Box2D"] = "%{wks.location}/Bento/vendor/Box2D/include"
IncludeDir["GLFW"] = "%{wks.location}/Bento/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Bento/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Bento/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Bento/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Bento/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Bento/vendor/entt/include"
IncludeDir["mono"] = "%{wks.location}/Bento/vendor/mono/include"
IncludeDir["shaderc"] = "%{wks.location}/Bento/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Bento/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{wks.location}/Bento/vendor/VulkanSDK/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{wks.location}/Bento/vendor/VulkanSDK/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/Bento/vendor/VulkanSDK/Lib"
LibraryDir["mono"] = "%{wks.location}/Bento/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}

Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

-- Windows Only --

Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "version.lib"
Library["BCrypt"] = "Bcrypt.lib"