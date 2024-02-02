#include "include/JsonReader.h"


JsonReader::JsonReader(const std::wstring& FileName) :FileOperator<std::wstring>(FileName)
{
	ReadContent(retFileData);
	auto JsonRoot = yyjson_read(retFileData.c_str(), retFileData.length(), 0);
	auto JsonVal = yyjson_doc_get_root(JsonRoot);
	mut_doc = yyjson_doc_mut_copy(JsonRoot, nullptr);
	mut_val = yyjson_mut_doc_get_root(mut_doc);
}


const std::string JsonReader::getStringValue(const std::string& Key, const std::string& ErrorValue)
{
	yyjson_mut_val* Val = yyjson_mut_obj_get(mut_val, Key.c_str());
	if (Val == nullptr) {
		return ErrorValue;
	}
	return yyjson_mut_get_str(Val);
}

bool JsonReader::setStringValue(const std::string& Key, const std::string& Value)
{
	yyjson_mut_val* emut_val = yyjson_mut_obj_get(mut_val, Key.c_str());
	if (emut_val == nullptr) {
		return false;
	}
	yyjson_mut_set_str(emut_val, Value.c_str());
	retFileData = yyjson_mut_write(mut_doc, YYJSON_WRITE_ESCAPE_UNICODE, NULL);
	return true;
}

bool JsonReader::setNumberValue(const std::string& Key, const int& Value)
{
	yyjson_mut_val* emut_val = yyjson_mut_obj_get(mut_val, Key.c_str());
	if (emut_val == nullptr) {
		return false;
	}
	yyjson_mut_set_int(emut_val, Value);
	return true;
}

const int JsonReader::getNumberValue(const std::string& Key, const int& ErrorValue)
{
	yyjson_mut_val* Val = yyjson_mut_obj_get(mut_val, Key.c_str());
	if (Val == nullptr) {
		return ErrorValue;
	}
	return yyjson_mut_get_int(Val);
}

bool JsonReader::writeCacheToFile()
{
	size_t len;
	char* json_str = yyjson_mut_write(mut_doc, 0, &len);
	if (json_str == nullptr) {
		return false;
	}
	std::string content(json_str, len);
	bool result = WriteContent(content);
	delete json_str;
	return result;
}

const std::string JsonReader::getJsonAll() {
	char* json_text = yyjson_mut_write(mut_doc, YYJSON_WRITE_ESCAPE_UNICODE, NULL);// 重新编码unicode字符
	std::unique_ptr<char[]> json_text_ptr(json_text);
	return std::string(json_text_ptr.get());
}

JsonReader::~JsonReader()
{
	if (mut_doc != nullptr) {
		yyjson_mut_doc_free(mut_doc);
	}
}
