#include "include/Util.h"
#include "include/NuCat.h"
#include <string>
#include <vector>

std::wstring ResolvePathAndTrimFile(std::wstring path)
{
    std::wstring::size_type pos = path.find_last_of(L"\\/");
    if (pos != std::wstring::npos)
    {
        return path.substr(0, pos);
    }
    return path;
}

bool WebViewIsInstall()
{
    LPWSTR version_info;
    GetAvailableCoreWebView2BrowserVersionString(nullptr, &version_info);
    if (version_info != L"")
    {
        return true;
    }
    return false;
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

std::wstring GetResourcePath(LPCWSTR _path) {
    std::wstring path = GetCurrentPath();
    std::wstring file = _path;
    std::wstring full_path = path + file;
    return full_path;
}
