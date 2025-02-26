project "App"
kind "ConsoleApp"
language "C++"
cppdialect "C++23"
staticruntime "off"

files { 
    "source/**.h", 
    "source/**.hpp", 
    "source/**.cpp"
}

includedirs {
    "source",
    "vendor/SFML3/include",
    -- "../graphing/include"
}

libdirs {
    "./vendor/SFML3/lib/%{cfg.buildcfg}",
}

links {
    -- os.matchfiles("vendor/SFML3/lib/%{cfg.buildcfg}/*.a"),
    "FLACd",
    "freetyped",
    "oggd",
    "sfml-audio-d",
    "sfml-audio-s-d",
    "sfml-graphics-d",
    "sfml-graphics-s-d",
    "sfml-main-s-d",
    "sfml-network-d",
    "sfml-network-s-d",
    "sfml-system-d",
    "sfml-system-s-d",
    "sfml-window-d",
    "sfml-window-s-d",
    "vorbisd",
    "vorbisencd",
    "vorbisfiled",
    -- "graphing"
}

targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
objdir ("../bin/int/" .. outputdir .. "/%{prj.name}")

filter "toolset:gcc"
    links {
        "mingw32"
    }

    buildoptions {
        "-Wall", "-Wno-unused"
    }

filter "system:windows"
    systemversion "latest"
    defines { "WINDOWS" }

filter "configurations:Debug"
    defines { "DEBUG" }
    runtime "Debug"
    symbols "On"

filter "configurations:Release"
    defines { "RELEASE" }
    runtime "Release"
    optimize "On"
    symbols "On"

filter "configurations:Dist"
    defines { "DIST" }
    runtime "Release"
    optimize "On"
    symbols "Off"