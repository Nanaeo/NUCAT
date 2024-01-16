#include "include/Theme.h"
ThemeLang::ThemeLang(std::string ThemeName, std::string LocalName)
{
	std::wstring LocalNameU16 = Utf8ToUtf16(LocalName);
	LocalNameU16.pop_back();//去掉\0
	std::wstring ThemeNameU16 = Utf8ToUtf16(ThemeName);
	ThemeNameU16.pop_back();//去掉\0
	std::wstring Local_PathU16 = L"\\Resource\\Theme\\"+ ThemeNameU16 +"Language\\" + LocalNameU16 + L".json";
	std::wstring Default_Path16 = L"\\Resource\\Theme\\" + ThemeNameU16 + "Language\\zh-CN.json";;

	std::wstring Local_Full_PathU16 = GetResourcePath(Local_PathU16.c_str());
	std::wstring Default_Full_PathU16 = GetResourcePath(Default_Path16.c_str());

	std::wstring Real_Full_PathU16 = (FileExists(Local_Full_PathU16.c_str()) ? Local_Full_PathU16.c_str() : Default_Full_PathU16.c_str());
	// 获取到文件位置

	FileOperator LanguageFileOperator(Real_Full_PathU16.c_str());
	LanguageFileOperator.read(retFileData);

	LanguageJsonRoot = yyjson_read(retFileData.c_str(), retFileData.length(), 0);
	LanguageJson = yyjson_doc_get_root(LanguageJsonRoot);
}

ThemeLang::~ThemeLang()
{
}

std::string ThemeLang::LanguageGet(std::string key)
{
	yyjson_val* Val = yyjson_obj_get(LanguageJson, key);
	if (Val == nullptr) {
		std::string ErrorText((const char*)u8"Not Load Language TEXT");
		return ErrorText;
	}
	return yyjson_get_str(Val);
}

std::string ThemeLang::LanguageGetAll()
{
	return retFileData;
}
