#pragma once
#include "include/DirectoryReader.h"
#include <Windows.h>
#include "include/JsonReader.h"
#include <vector>
#include <string>
#include "yyjson.h"
class Theme:public JsonReader
{
public:
	std::wstring getFilePath(std::string ThemeName);
	Theme(std::string ThemeName);
	~Theme();
	std::string SDKGetVersion();
	static std::string GetThemeEntry(std::string ThemeName);
	static std::string GetThemeFile(std::string ThemeName, std::string FilePath);
	static std::vector<std::string> ListThemePathU8();
	static std::vector<std::wstring> ListThemePathW();
private:
	std::string _ThemeName;
	std::string retFileData;
};