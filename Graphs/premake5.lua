project "Graphs"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/obj/" .. outputdir .. "/%{prj.name}")

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

    links {
        sfml.determineLibs();
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