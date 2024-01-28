#pragma once
#include <iostream>
#include <Windows.h>
#include "include/JsonReader.h"
class Settings : public JsonReader
{
public:
	static Settings* instance;
	std::string GetThemeU8();
	std::wstring GetThemeW();
	Settings();
	~Settings();
	static Settings* getInstance();
private:

};
