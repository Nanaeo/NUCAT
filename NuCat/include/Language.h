#pragma once
#include <iostream>
#include <Windows.h>
#include "include/JsonReader.h"
#include "include/Util.h"
class Language :public JsonReader
{
public:
	Language(const std::string& id, std::wstring langfile);
	~Language();
	const std::string& getId() const;
	const std::wstring TextW(const std::string& Key, const std::string& ErrorValue = "Load Error");
private:
	std::string _id;
};
