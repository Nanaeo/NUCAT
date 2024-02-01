#include "include/JsonReader.h"

JsonReader::JsonReader(const std::wstring& FileName) :FileOperator<std::wstring>(FileName)
{
	ReadContent(retFileData);
	JsonRoot = yyjson_read(retFileData.c_str(), retFileData.length(), 0);
	JsonVal = yyjson_doc_get_root(JsonRoot);
}

const std::string JsonReader::getStringValue(const std::string& Key, const std::string& ErrorValue)
{
	yyjson_val* Val = yyjson_obj_get(JsonVal, Key.c_str());
	if (Val == nullptr) {
		return ErrorValue;
	}
	return yyjson_get_str(Val);
}

bool JsonReader::setStringValue(const std::string& Key, const std::string& Value)
{
	yyjson_mut_doc* mut_doc = yyjson_doc_mut_copy(JsonRoot, nullptr);
	if (mut_doc == nullptr) {
		return false;
	}

	yyjson_mut_val* mut_val = yyjson_mut_obj_get(yyjson_mut_doc_get_root(mut_doc), Key.c_str());
	if (mut_val == nullptr) {
		return false;
	}
	yyjson_mut_set_str(mut_val, Value.c_str());
	JsonRoot = yyjson_mut_doc_imut_copy(mut_doc, nullptr);
	JsonVal = yyjson_doc_get_root(JsonRoot);
	retFileData = yyjson_mut_write(mut_doc, YYJSON_WRITE_ESCAPE_UNICODE, NULL);
	return true;
}

bool JsonReader::setNumberValue(const std::string& Key, const int& Value)
{
	yyjson_mut_doc* mut_doc = yyjson_doc_mut_copy(JsonRoot, nullptr);
	if (mut_doc == nullptr) {
		return false;
	}
	yyjson_mut_val* mut_val = yyjson_mut_obj_get(yyjson_mut_doc_get_root(mut_doc), Key.c_str());
	if (mut_val == nullptr) {
		return false;
	}
	yyjson_mut_set_int(mut_val, Value);
	yyjson_doc_free(JsonRoot);
	JsonRoot = yyjson_mut_doc_imut_copy(mut_doc, nullptr);
	JsonVal = yyjson_doc_get_root(JsonRoot);
	retFileData = yyjson_mut_write(mut_doc, YYJSON_WRITE_ESCAPE_UNICODE, NULL);
	return true;
}

const int JsonReader::getNumberValue(const std::string& Key, const int& ErrorValue)
{
	yyjson_val* Val = yyjson_obj_get(JsonVal, Key.c_str());
	if (Val == nullptr) {
		return ErrorValue;
	}
	return yyjson_get_int(Val);
}

bool JsonReader::writeCacheToFile()
{
	size_t len;
	char* json_str = yyjson_write(JsonRoot, 0, &len);
	if (json_str == nullptr) {
		return false;
	}
	std::string content(json_str, len);
	bool result = WriteContent(content);
	delete json_str;
	return result;
}

const std::string JsonReader::getJsonAll() {
	yyjson_mut_doc* mut_doc = yyjson_doc_mut_copy(JsonRoot, nullptr);
	char* json_text = yyjson_mut_write(mut_doc, YYJSON_WRITE_ESCAPE_UNICODE, NULL);// 重新编码unicode字符
	std::unique_ptr<char[]> json_text_ptr(json_text);
	return std::string(json_text_ptr.get());
}

JsonReader::~JsonReader()
{
	if (JsonRoot != nullptr) {
		yyjson_doc_free(JsonRoot);
		JsonRoot = nullptr;
		JsonVal = nullptr;
	}
}
