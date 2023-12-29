#include "include/Language.h"
#include "include/Util.h"
#include "include/FileOperator.h"
namespace Language
{
	yyjson_val* LanguageJson = nullptr;
	yyjson_doc* LanguageJsonRoot = nullptr;
	void Language::Init(std::string LocalName);
	std::wstring TextW(const char* key);
	std::string TextU8(const char* key);

};
void Language::Init(std::string LocalName)
{
	std::wstring LocalNameU16 = Utf8ToUtf16(LocalName);
	LocalNameU16.pop_back();//去掉\0
	std::wstring Local_PathU16 = L"\\Language\\" + LocalNameU16 + L".json";
	std::wstring Default_Path16 = L"\\Language\\zh-CN.json";

	std::wstring Local_Full_PathU16 = GetResourcePath(Local_PathU16.c_str());
	std::wstring Default_Full_PathU16 = GetResourcePath(Default_Path16.c_str());

	std::wstring Real_Full_PathU16 = (FileExists(Local_Full_PathU16.c_str()) ? Local_Full_PathU16.c_str() : Default_Full_PathU16.c_str());
	// 获取到文件位置

	FileOperator LanguageFileOperator(Real_Full_PathU16.c_str());
	std::string retFileData;
	LanguageFileOperator.read(retFileData);

	LanguageJsonRoot = yyjson_read(retFileData.c_str(), retFileData.length(), 0);
	LanguageJson = yyjson_doc_get_root(LanguageJsonRoot);
}
std::wstring Language::TextW(const char* key)
{
	std::wstring retdata = Utf8ToUtf16(Language::TextU8(key));
	return retdata;
}
std::string Language::TextU8(const char* key)
{
	yyjson_val* Val = yyjson_obj_get(LanguageJson, key);
	if (Val == nullptr) {
		std::string ErrorText((const char*)u8"Not Load Language TEXT");
		return ErrorText;
	}
	return yyjson_get_str(Val);
}
