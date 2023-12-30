#include "include/Util.h"
#include <string>
#include <vector>
#include <chrono>
#include <format>
// 工具类
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
std::string GetConfigDefaultLocaleName() {
	wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
	int result = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
	if (result > 0) {
		std::wstring localeNameU16(localeName);
		std::string localNameU8(Utf16ToUtf8(localeNameU16));
		localNameU8.pop_back();
		return (char *)(localNameU8.c_str());
	}
	else {
		return "zh-CN";
	}
}
bool FileExists(const std::wstring& fileName) {
	DWORD fileAttributes = GetFileAttributesW(fileName.c_str());
	if (fileAttributes == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	return true;
}
std::string getCurrentDate() {
	const auto now = std::chrono::system_clock::now();
	const auto time_zone = std::chrono::current_zone();
	const auto local_time = time_zone->to_local(now);
	const auto time_point = std::chrono::time_point_cast<std::chrono::days>(local_time);
	const auto year_month_day = std::chrono::year_month_day{ time_point };
	return std::format("{:%Y-%m-%d}", year_month_day);
}
std::string getCurrentDateTime() {
	const auto now = std::chrono::system_clock::now();
	const auto time_zone = std::chrono::current_zone();
	const auto local_time = time_zone->to_local(now);
	const auto time_point = std::chrono::floor<std::chrono::seconds>(local_time);
	const auto year_month_day = std::chrono::year_month_day{ time_point };
	const auto time_of_day = std::chrono::hh_mm_ss{ time_point - std::chrono::floor<std::chrono::days>(time_point) };
	return std::format("{:%Y-%m-%d %H:%M:%S}", year_month_day, time_of_day);
}
std::string getCurrentTimestamp() {
	const auto now = std::chrono::system_clock::now();
	const auto duration = now.time_since_epoch();
	const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	return std::format("{}", millis);
}
std::string GetResourcePathU8(char * _path) {
	std::wstring path = GetCurrentPath();
	std::wstring file = Utf8ToUtf16(_path);
	std::wstring full_path = path + file;
	std::string full_path_u8 = Utf16ToUtf8(full_path);
	return full_path_u8;
}
std::string GetResourceU8(char* _file) {
	std::wstring path = GetCurrentPath();
	std::wstring file = Utf8ToUtf16(_file);
	std::wstring full_path = L"file:\\\\\\" + path + L"\\" + file;
	std::string full_path_u8 = Utf16ToUtf8(full_path);
	return full_path_u8;
}
