#pragma once
#include <iostream>
#include <include/yyjson.h>
#include <Windows.h>
class NuSetting
{
public:
	NuSetting();
	~NuSetting();
	std::string GetKeyStr(const char* key);
	void SetKey();

private:
	HANDLE SettingFile = nullptr;
	yyjson_val* SettingJson = nullptr;
	yyjson_doc* SettingJsonRoot = nullptr;
};