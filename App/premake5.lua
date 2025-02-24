    project "App"
    kind "WindowedApp"
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
        "../graphing/include"
    }
    
    libdirs {
        "vendor/SFML3/lib/%{cfg.buildcfg}"
    }

    links {
        -- os.matchfiles("vendor/SFML3/lib/%{cfg.buildcfg}/*.a"),
        "libFLACd.a",
        "libfreetyped.a",
        "liboggd.a",
        "libsfml-audio-d.a",
        "libsfml-audio-s-d.a",
        "libsfml-graphics-d.a",
        "libsfml-graphics-s-d.a",
        "libsfml-main-s-d.a",
        "libsfml-network-d.a",
        "libsfml-network-s-d.a",
        "libsfml-system-d.a",
        "libsfml-system-s-d.a",
        "libsfml-window-d.a",
        "libsfml-window-s-d.a",
        "libvorbisd.a",
        "libvorbisencd.a",
        "libvorbisfiled.a",
        "graphing"
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