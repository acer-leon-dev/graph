-- premake5.lua
workspace "New Project"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

-- group "Graphing"
	-- include "graphing/premake5.lua"
-- group ""

include "app/premake5.lua"