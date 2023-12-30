#pragma once
#include <iostream>
#include <include/yyjson.h>
#include <Windows.h>

namespace Language
{
	extern yyjson_val* LanguageJson;
	extern yyjson_doc* LanguageJsonRoot;
	void Init(std::string LocalName);
	std::wstring TextW(const char* key);
	std::string TextU8(const char* key);
	std::string TextU8Theme(const char* key);
	std::string TextWTheme(const char* key);
	std::string TextU8ThemeAll();
	std::string TextWThemeAll();
};


