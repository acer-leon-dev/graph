sfml = {}

sfml.determineLibs = function ()
    local libs_list = nil

    if '%{cfg.buildcfg}' == "Debug" then
        libs_list = {
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
    else
        libs_list = {
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
    end
    return table.unpack(libs_list)
end

-- sfml.copySharedLibs = function (sharedlibdir, targetdir)
--     local sharedlibs_list = nil
    
--     if '%{cfg.buildcfg}' == "Debug" then
--         sharedlibs_list = {
--             "sfml-audio-d-3.dll",
--             "sfml-graphics-d-3.dll",
--             "sfml-network-d-3.dll",
--             "sfml-system-d-3.dll",
--             "sfml-window-d-3.dll",
--         }
--     else
--         sharedlibs_list = {
--             "sfml-audio-3.dll",
--             "sfml-graphics-3.dll",
--             "sfml-network-3.dll",
--             "sfml-system-3.dll",
--             "sfml-window-3.dll",
--         }
--     end

--     -- local sharedlibdir = "%{wks.location}/Graphs/vendor/SFML3/bin"
--     -- local targetdir = "%{wks.location}/bin/" .. outputdir .. "/%{prj.name}  "
--     for _, library_name in ipairs(sharedlibs_list) do
--         local ok, err = os.copyfile(path.join(sharedlibdir, library_name), targetdir)

--         if not ok then
--             io.write(err)
--         end
--     end
-- end