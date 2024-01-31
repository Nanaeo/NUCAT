#include "include/WebBind.h"
#include "include/yyjson.h"
#include "include/Util.h"

std::string WebBind::Vstring2Json(const std::vector<std::string>& data)
{
	yyjson_mut_doc* doc = yyjson_mut_doc_new(NULL);
	if (!doc) return "";
	yyjson_mut_val* arr = yyjson_mut_arr(doc);
	if (!arr) {
		yyjson_mut_doc_free(doc);
		return "";
	}
	for (const auto& item : data) {
		yyjson_mut_val* str = yyjson_mut_str(doc, item.c_str());
		if (!str || !yyjson_mut_arr_append(arr, str)) {
			yyjson_mut_doc_free(doc);
			return "";
		}
	}
	yyjson_mut_val* obj = yyjson_mut_obj(doc);
	if (!obj) {
		yyjson_mut_doc_free(doc);
		return "";
	}
	yyjson_mut_val* key = yyjson_mut_str(doc, "data");
	if (!key || !yyjson_mut_obj_add(obj, key, arr)) {
		yyjson_mut_doc_free(doc);
		return "";
	}
	yyjson_mut_doc_set_root(doc, obj);
	char* json_text = yyjson_mut_write(doc, YYJSON_WRITE_ESCAPE_UNICODE, NULL);
	std::string result = json_text ? json_text : "";
	yyjson_mut_doc_free(doc);
	free(json_text);
	return result;
}
std::string WebBind::String2Json(const std::string& data) {
	std::string _data = data;
	std::string toReplace = "\"";
	std::string replaceWith = "\\\"";
	size_t pos = 0;
	while ((pos = _data.find(toReplace, pos)) != std::string::npos) {
		_data.replace(pos, toReplace.length(), replaceWith);
		pos += replaceWith.length();
	}
	std::string _data_handle = utf8_to_escape_sequenceWithoutAscii(_data);
	std::string _ret = (char*)u8"{\"data\":\"" + _data_handle + (char*)u8"\"}";
	return  _ret;
}
std::string WebBind::Number2Json(int data) {
	std::string _ret = (char*)u8"{\"data\":\"" + std::to_string(data) + (char*)u8"\"}";
	return  _ret;
}
std::string WebBind::Bool2Json(bool data) {
	std::string _ret;
	if (data) {
		_ret = (char*)u8"{\"data\":true}";
	}
	else {
		_ret = (char*)u8"{\"data\":false}";
	}
	return  _ret;
}
// 下面实现JSB部分