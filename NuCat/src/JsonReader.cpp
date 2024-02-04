#include "include/JsonReader.h"


JsonReader::JsonReader(const std::wstring& FileName) :FileOperator<std::wstring>(FileName)
{
	ReadContent(retFileData);
	JsonRoot = json::parse(retFileData);
	if (!JsonRoot) {
		// Throw出去Log记录 
		return;
	}
}

const std::string JsonReader::getStringValue(const std::string& Key, const std::string& ErrorValue)
{
	json::value& JsonCopy = *JsonRoot;
	return JsonCopy.get(Key, ErrorValue);
}

bool JsonReader::setStringValue(const std::string& Key, const std::string& Value)
{
	json::value& JsonCopy = *JsonRoot;
	JsonCopy[Key] = Value;
	return true;
}

bool JsonReader::setNumberValue(const std::string& Key, const int& Value)
{
	json::value& JsonCopy = *JsonRoot;
	JsonCopy[Key] = Value;
	return true;
}

const int JsonReader::getNumberValue(const std::string& Key, const int& ErrorValue)
{
	json::value& JsonCopy = *JsonRoot;
	return JsonCopy.get(Key, ErrorValue);
}

bool JsonReader::writeCacheToFile()
{
	json::value& JsonCopy = *JsonRoot;
	bool result = WriteContent(JsonCopy.to_string());
	return result;
}

const std::string JsonReader::getJsonAll() {
	json::value& JsonCopy = *JsonRoot;
	return JsonCopy.to_string();
}

JsonReader::~JsonReader()
{
}
