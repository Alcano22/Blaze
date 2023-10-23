project "Sandbox"
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
        -- "%{wks.location}/Blaze/vendor/spdlog/include",
        "%{wks.location}/Blaze/src",
        -- "%{wks.location}/Blaze/vendor",
        -- "%{IncludeDir.glm}"
    }

    links
    {
        "Blaze"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BLZ_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "BLZ_DEBUG"
        buildoptions "/MDd"
        runtime "Debug"
        symbols "on"

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