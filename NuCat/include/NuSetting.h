#pragma once
#include "include/Header.h"
#include "include/Util.h"
#include <Windows.h>
class NuSetting
{
public:
	NuSetting();
	~NuSetting();
	const char* GetKeyStr(const char* key);
	void SetKey();

private:
	HANDLE SettingFile;
	char* ContentPtr;
	int ContentLen;
	yyjson_val* SettingJson;
	yyjson_doc* SettingJsonRoot;
};