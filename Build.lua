-- premake5.lua
workspace "New Project"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Graph"
	include "Graph/Build-Graph.lua"
group ""

include "App/Build-App.lua"