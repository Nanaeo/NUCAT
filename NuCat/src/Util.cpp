#include "include/Util.h"
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <format>
#include <algorithm>
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
	utf8.pop_back();
	return utf8;
}
std::wstring Utf8ToUtf16(const std::string& utf8) {
	int length = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, NULL, 0);
	std::wstring utf16(length, 0);
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], length);
	utf16.pop_back();
	return utf16;
}

std::string GetConfigDefaultLocaleName() {
	wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
	int result = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
	if (result > 0) {
		std::wstring localeNameU16(localeName);
		std::string localNameU8(Utf16ToUtf8(localeNameU16));
		return (char*)(localNameU8.c_str());
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
	const auto year_month_day = std::chrono::year_month_day{ std::chrono::floor<std::chrono::days>(time_point) };
	const auto time_of_day = std::chrono::hh_mm_ss{ time_point - std::chrono::floor<std::chrono::days>(time_point) };
	std::ostringstream oss;
	oss << std::format("{:%Y-%m-%d}", year_month_day) << ' '
		<< std::setw(2) << std::setfill('0') << time_of_day.hours().count() << ':'
		<< std::setw(2) << std::setfill('0') << time_of_day.minutes().count() << ':'
		<< std::setw(2) << std::setfill('0') << time_of_day.seconds().count();

	return oss.str();
}
std::string getCurrentTimestamp() {
	const auto now = std::chrono::system_clock::now();
	const auto duration = now.time_since_epoch();
	const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	return std::format("{}", millis);
}
std::string GetResourcePathU8(char* _path) {
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
bool ProgramIsAdmin() {
	BOOL isAdmin = FALSE;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	isAdmin = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);
	if (isAdmin) {
		CheckTokenMembership(NULL, AdministratorsGroup, &isAdmin);
		FreeSid(AdministratorsGroup);
	}
	return isAdmin;
}
std::wstring getExtensionLowercase(const std::wstring& filepath) {
	std::size_t pos = filepath.rfind(L'.');
	if (pos == std::wstring::npos) return L"";
	std::wstring extension = filepath.substr(pos);
	std::transform(extension.begin(), extension.end(), extension.begin(), ::towlower);
	return extension;
}
std::string getExtensionLowercaseU8(const std::string& filepath) {
	std::size_t pos = filepath.rfind('.');
	if (pos == std::string::npos) return "";
	std::string extension = filepath.substr(pos);
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
	return extension;
}


std::string utf8_to_escape_sequence(const std::string& utf8_str) {
	int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wlen];
	MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, wstr, wlen);

	std::ostringstream oss;
	for (int i = 0; i < wlen; ++i) {
		oss << "\\u" << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(wstr[i]);
	}

	delete[] wstr;
	return oss.str();
}
std::string escape_sequence_to_utf8(const std::string& escape_sequence) {
	std::wstringstream wss;
	for (size_t i = 0; i < escape_sequence.length(); i += 6) {
		std::string hex = escape_sequence.substr(i + 2, 4);
		wchar_t wc = static_cast<wchar_t>(std::stoi(hex, nullptr, 16));
		wss << wc;
	}

	std::wstring unicode_str = wss.str();
	int len = WideCharToMultiByte(CP_UTF8, 0, unicode_str.c_str(), -1, NULL, 0, NULL, NULL);
	char* str = new char[len];
	WideCharToMultiByte(CP_UTF8, 0, unicode_str.c_str(), -1, str, len, NULL, NULL);

	std::string result(str);
	delete[] str;
	return result;
}
std::string utf8_to_escape_sequenceWithoutAscii(const std::string& utf8_str) {
	int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wlen];
	MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, wstr, wlen);
	std::ostringstream oss;
	for (int i = 0; i < wlen; ++i) {
		if (wstr[i] >= 0 && wstr[i] <= 127) { // ASCII范围
			oss << static_cast<char>(wstr[i]);
		}
		else {
			oss << "\\u" << std::setfill('0') << std::setw(4) << std::hex << static_cast<int>(wstr[i]);
		}
	}
	delete[] wstr;
	return oss.str();
}
std::string escape_sequence_to_utf8WithoutAscii(const std::string& str) {
	std::ostringstream oss;
	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] == '\\' && i + 1 < str.size() && str[i + 1] == 'u') {
			std::string hex = str.substr(i + 2, 4);
			int unicode;
			std::istringstream(hex) >> std::hex >> unicode;
			wchar_t wstr[] = { static_cast<wchar_t>(unicode), 0 };
			char utf8[5] = { 0 };
			WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, sizeof(utf8), NULL, NULL);
			oss << utf8;
			i += 5; // 跳过已处理的字符
		}
		else {
			oss << str[i];
		}
	}
	return oss.str();
}