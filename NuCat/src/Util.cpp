#include "include/Util.h"
#include "include/NuCat.h"
#include <string>
#include <vector>
#include <codecvt>
bool CompareWchatText(const std::wstring& text1, const std::wstring& text2)
{
	return text1.compare(text2) == 0;
}

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
	if (!CompareWchatText(L"", version_info))
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
std::wstring Get7ZipInstallPath() {
	HKEY hKey;
	std::wstring path;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\7-Zip", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		DWORD type;
		DWORD size = MAX_PATH;
		WCHAR buffer[MAX_PATH];
		if (RegGetValue(hKey, NULL, L"Path", RRF_RT_REG_SZ, &type, buffer, &size) == ERROR_SUCCESS) {
			path = buffer;
		}
		RegCloseKey(hKey);
	}
	return path;
}
std::string Utf16ToUtf8(const std::wstring& utf16) {
	int length = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, NULL, 0, NULL, NULL);
	std::string utf8(length, 0);
	WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, &utf8[0], length, NULL, NULL);
	return utf8;
}
std::wstring Utf8ToUtf16(const std::string& utf8) {
	int length = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
	std::wstring utf16(length, 0);
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], length);
	return utf16;
}
std::string U8GetUserDefaultLocaleName(){
	wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
	int result = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
	if (result > 0) {
		std::wstring localNameU16(localeName);
		return Utf16ToUtf8(localNameU16);
	}
	else {
		return (char*)u8"zh-CN";
	}
}
bool FileExists(const std::wstring& fileName){
	DWORD fileAttributes = GetFileAttributesW(fileName.c_str());
	if (fileAttributes == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	return true;
}
std::string NuCatGetRealDefaultLocaleName() {
	NuSetting _NUCAT_SETTING;
	std::string Setting_LanguageString = _NUCAT_SETTING.GetKeyStr("Language");
	const char* Setting_Language = Setting_LanguageString.c_str();
	std::string Setting_LanguageU8(Setting_Language);
	std::string Default_LanguageU8 = U8GetUserDefaultLocaleName();
	if (Setting_LanguageU8.compare((const char *)u8"") != 0) {
		return Setting_LanguageU8;
	}
	return Default_LanguageU8;

}