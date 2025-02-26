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
    "./vendor/SFML3/bin/%{cfg.buildcfg}"
}

SFML_Libs = {
    "sfml-audio",
    "sfml-audio-s",
    "sfml-graphics",
    "sfml-graphics-s",
    "sfml-main-s",
    "sfml-network",
    "sfml-network-s",
    "sfml-system",
    "sfml-system-s",
    "sfml-window",
    "sfml-window-s"
}

SFML_Dependency_Libs = {
    "ogg",
    "FLAC",
    "freetype",
    "vorbis",
    "vorbisenc",
    "vorbisfile"
}

if "%{cfg.buildcfg}" == "Debug" then
    for i,v in ipairs(SFML_Libs) do SFML_Libs[i] = v .. "-d" end
    for i,v in ipairs(SFML_Dependency_Libs) do SFML_Libs[i] = v .. "d" end
end
    
links {
    -- table.unpack(SFML_Libs),
    -- table.unpack(SFML_Dependency_Libs),
    "FLACd",
    "freetyped",
    "oggd",
    "vorbisd",
    "vorbisencd",
    "vorbisfiled",
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

    "sfml-audio-d-3.dll",
    "sfml-graphics-d-3.dll",
    "sfml-network-d-3.dll",
    "sfml-system-d-3.dll",
    "sfml-window-d-3.dll"
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
