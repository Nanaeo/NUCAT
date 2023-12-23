#include "include/Util.h"
#include <string>
std::wstring ResolvePathAndTrimFile(std::wstring path)
{
    std::wstring::size_type pos = path.find_last_of(L"\\/");
    if (pos != std::wstring::npos)
    {
        return path.substr(0, pos);
    }
    return path;
}

std::wstring GetCurrentPath()
{
    wchar_t appPath[MAX_PATH];
    GetModuleFileNameW(nullptr, appPath, ARRAYSIZE(appPath));
    return ResolvePathAndTrimFile(appPath);
}

std::wstring GetResourceEntry() {
    std::wstring path = GetCurrentPath();
    std::wstring file = L"Resource\\index.html";
    std::wstring full_path = L"file:\\\\\\" + path + L"\\" + file;
    return full_path;
}
