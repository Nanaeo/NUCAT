#include "include/Settings.h"
#include "include/Util.h"
#include "include/FileOperator.h"
// 不需要SettingJsonRoot回收

HANDLE Settings::SettingFile = nullptr;
yyjson_val* Settings::SettingJson = nullptr;
yyjson_doc* Settings::SettingJsonRoot = nullptr;

void Settings::Init()
{
	std::wstring SettingPath = GetResourcePath(L"\\Config\\Settings.json");
	FileOperator SettingFileOperator(SettingPath.c_str());
	std::string retFileData;
	SettingFileOperator.read(retFileData);
	SettingJsonRoot = yyjson_read(retFileData.c_str(), retFileData.length(), 0);
	SettingJson = yyjson_doc_get_root(SettingJsonRoot);
}

std::string Settings::GetKeyStr(const char* key, const char* errorText = nullptr)
{
	yyjson_val* Val = yyjson_obj_get(Settings::SettingJson, key);
	if (Val == nullptr) {
		if (errorText == nullptr) return "";
		return errorText;
	}
	return yyjson_get_str(Val);
}

std::string  Settings::GetThemeU8() 
{
	std::string DefaultTheme = Settings::GetKeyStr((char*)u8"Theme", (char*)u8"default");
	if (DefaultTheme.compare("") == 0) return (char*)u8"default";
	return DefaultTheme;
}

std::wstring  Settings::GetThemeW() {
	std::wstring DefaultTheme = Utf8ToUtf16(Settings::GetThemeU8());
	return DefaultTheme;
}
// 未实现
void Settings::SetKey()
{

}