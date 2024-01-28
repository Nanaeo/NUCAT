#pragma once
#include <iostream>
#include <include/yyjson.h>
#include <Windows.h>
namespace Settings {
	extern HANDLE SettingFile;
	extern yyjson_val* SettingJson;
	extern yyjson_doc* SettingJsonRoot;
	void Init();
	std::string GetKeyStr(const char* key, const char* errorText);
	std::string GetThemeU8();
	std::wstring GetThemeW();
	void SetKey();
}