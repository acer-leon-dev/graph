include "scripts/premake/sfml.lua"

workspace "Graph"
   architecture "x86_64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["SFML"] = "%{!wks.location}/Graphs/vendor/SFML3/include"

LibraryDir = {}
LibraryDir["SFML"] = "%{!wks.location}/Graphs/vendor/SFML3/lib/%{cfg.buildcfg}"

group "Graphs"
   include "Graphs"
group ""