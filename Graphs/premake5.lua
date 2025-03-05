project "Graphs"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/obj/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.hpp"
    pchsource "pch.cpp"

    includedirs {
        "src",
        IncludeDir["SFML"],
    }

    libdirs {
        LibraryDir["SFML"],
    }
    
    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp"
    }

    filter "toolset:gcc or toolset:clang"
        buildoptions {
            "-Wall",
            "-Wno-unused"
        }

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    -- Configurations

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

        links {
            "FLACd",
            "freetyped",
            "oggd",
            "vorbisd",
            "vorbisencd",
            "vorbisfiled",
    
            "sfml-audio-s-d",
            "sfml-audio-d",
            "sfml-graphics-s-d",
            "sfml-graphics-d",
            "sfml-main-s-d",
            "sfml-network-s-d",
            "sfml-network-d",
            "sfml-system-s-d",
            "sfml-system-d",
            "sfml-window-s-d",
            "sfml-window-d",
        }

    filter "not configurations:Debug"
        links {
            "FLAC",
            "freetype",
            "ogg",
            "vorbis",
            "vorbisenc",
            "vorbisfile",

            "sfml-audio-s",
            "sfml-audio",
            "sfml-graphics-s",
            "sfml-graphics",
            "sfml-main-s",
            "sfml-network-s",
            "sfml-network",
            "sfml-system-s",
            "sfml-system",
            "sfml-window-s",
            "sfml-window",
        }
        
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