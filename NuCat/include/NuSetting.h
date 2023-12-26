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
	HANDLE SettingFile;
	char* ContentPtr;
	int ContentLen;
	yyjson_val* SettingJson;
	yyjson_doc* SettingJsonRoot;
};