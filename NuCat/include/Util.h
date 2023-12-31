#pragma once
#include <iostream>
#include <Windows.h>
std::wstring GetResourceEntry();
std::wstring GetCurrentPath();
std::wstring ResolvePathAndTrimFile(std::wstring path);
std::wstring GetResourcePath(LPCWSTR _path);
std::wstring Get7ZipInstallPath();
std::wstring Utf8ToUtf16(const std::string& utf8);
std::string Utf16ToUtf8(const std::wstring& utf16);
bool CompareWchatText(const std::wstring& text1, const std::wstring& text2);
std::string GetConfigDefaultLocaleName();
bool FileExists(const std::wstring& fileName);
std::string getCurrentDate();
std::string getCurrentTimestamp();
std::string GetResourcePathU8(char* _path);
std::string GetResourceU8(char* _file);
std::string getCurrentDateTime();
bool ProgramIsAdmin();
std::wstring getExtensionLowercase(const std::wstring& filepath);
std::string getExtensionLowercase(const std::string& filepath);
std::string utf8_to_escape_sequence(const std::string& utf8_str);
std::string escape_sequence_to_utf8(const std::string& escape_sequence);