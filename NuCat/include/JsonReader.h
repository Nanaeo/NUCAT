#pragma once
#include "include/FileOperator.h"
#include "include/Util.h"
#include "include/json.hpp"
#include <memory>
#include <any>
class JsonReader :private FileOperator< std::wstring >
{
public:
	JsonReader(const std::wstring& FileName);
	bool setStringValue(const std::string& Key, const std::string& Value);
	const std::string getStringValue(const std::string& Key, const std::string& ErrorValue = "Load Error");
	bool setNumberValue(const std::string& Key, const int& Value);
	const int getNumberValue(const std::string& Key, const int& ErrorValue = 0);
	bool writeCacheToFile();
	const std::string getJsonAll();
	//保持内存内容到文件
	~JsonReader();

private:
	std::string retFileData = "";
	std::optional<json::value> JsonRoot;
};