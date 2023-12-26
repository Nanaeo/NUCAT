#pragma once
#include "include/Header.h"
class Language
{
public:
	Language(std::string LocalName);
	~Language();

private:
	HANDLE LanguageFile;
	char* ContentPtr;
	int ContentLen;
	yyjson_val* LanguageJson;
	yyjson_doc* LanguageJsonRoot;
};

