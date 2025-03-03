#include "systemfont.hpp"
#include <filesystem>

#ifdef _WIN32

#include <initguid.h>
#include <knownfolders.h>
#include <shlobj.h>

namespace fs = std::filesystem;

// Returns empty if directory could not be foud.
// `result.empty() == true` on fail
std::string getSystemFontsDirectory()
{
    // Get Windows directory path with winapi
    
    // char * buffer;
    // UINT ok = GetSystemWindowsDirectoryA(buffer, 255);
    // if (!ok)
    // {
    //     return "";
    // }
    // fs::path fonts_path = fs::path(buffer) / "Fonts";

    wchar_t * buffer = new wchar_t[255];
    HRESULT res = SHGetKnownFolderPath(FOLDERID_Fonts, 0, NULL, &buffer);
    if (res != S_OK)
    {
        delete[] buffer;
        return "";
    }
    fs::path fonts_path{buffer};
    delete[] buffer;
    
    return fonts_path.string();
}

std::string findSystemFont(std::string file)
{
    fs::path font_path = fs::path(getSystemFontsDirectory()) / file;
    if (fs::exists(font_path))
    {
        return font_path.string();
    }
    else
    {
        return "";
    }
}

#elifdef __unix__

#include <system_error>

std::string getSystemFontsDirectory()
{
    throw std::system_error("This OS is not supported");
}

#endif