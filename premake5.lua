include "dependencies.lua"

workspace "Blaze"
    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    -- include "Blaze/vendor/GLFW"
    -- include "Blaze/vendor/Glad"
    -- include "Blaze/vendor/imgui"
group ""

group "Core"
    include "Blaze"
    include "Sandbox"
group ""