function SFML_determineLibraries()
    local libs_list = {
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

    if '%{cfg.buildcfg}' == "Debug" then
        for i, libname in ipairs(libs_list) do
            if string.startswith(lib, "sfml") then
                libs_list[i] = libname .. "-d"
            else
                libs_list[i] = libname .. "d"
            end
        end
    end

    return table.unpack(libs_list)
end