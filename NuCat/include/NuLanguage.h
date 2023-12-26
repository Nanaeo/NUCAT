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
	HANDLE LanguageFile = nullptr;
	char* ContentPtr = nullptr;
	int ContentLen = 0;
	yyjson_val* LanguageJson = nullptr;
	yyjson_doc* LanguageJsonRoot = nullptr ;
};

