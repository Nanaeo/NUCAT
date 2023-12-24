#pragma once

#include "include/Header.h"
//#define int64 (long long)
std::wstring GetResourceEntry();
std::wstring GetCurrentPath();
std::wstring ResolvePathAndTrimFile(std::wstring path);
bool WebViewIsInstall();
std::wstring GetResourcePath(LPCWSTR _path);
std::wstring Get7ZipInstallPath();