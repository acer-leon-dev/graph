project "Graphs"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    files { 
        "src/**.h", 
        "src/**.hpp", 
        "src/**.cpp"
    }

    includedirs {
        "src",
        IncludeDir["SFML"],
    }

    libdirs {
        "./vendor/SFML3/lib/%{cfg.buildcfg}",
    }

    links {
        SFML_determineLibraries();
    }

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/obj/" .. outputdir .. "/%{prj.name}")

    filter "toolset:gcc or toolset:clang"
        buildoptions {
            "-Wall",
            "-Wno-unused"
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