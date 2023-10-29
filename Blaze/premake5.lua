project "Blaze"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "blzpch.h"
    pchsource "src/blzpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp",
        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        
        defines 
        {
            "BLZ_PLATFORM_WINDOWS",
            "BLZ_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        buildoptions "/MDd"
        runtime "Debug"
        symbols "on"

        defines 
        {
            "BLZ_DEBUG",
            "BLZ_ENABLE_ASSERTS"
        }

    filter "configurations:Release"
        defines "BLZ_RELEASE"
        buildoptions "/MD"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BLZ_DIST"
        buildoptions "/MD"
        runtime "Release"
        optimize "on"