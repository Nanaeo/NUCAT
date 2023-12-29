#pragma once
#include "include/Header.h"
class NuLanguage
{
public:
	NuLanguage(std::string LocalName);
	~NuLanguage();
	std::wstring TextW(const char* key);
	std::string TextU8(const char* key);
private:
	yyjson_val* LanguageJson = nullptr;
	yyjson_doc* LanguageJsonRoot = nullptr ;
};

