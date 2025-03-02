include "premake/sfml.lua"

workspace "Graph"
   architecture "x86_64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["SFML"] = "%{wks.location}/Graphs/src/vendor/SFML3/include"

group "Graphs"
   include "Graphs"
group ""