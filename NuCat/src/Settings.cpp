#include "include/Settings.h"
#include "include/Util.h"
#include "include/FileOperator.h"
// 不需要SettingJsonRoot回收
namespace Settings {
	HANDLE SettingFile = nullptr;
	yyjson_val* SettingJson = nullptr;
	yyjson_doc* SettingJsonRoot = nullptr;
	void Init();
	std::string GetKeyStr(const char* key);
	void SetKey();
}
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
void Settings::SetKey()
{

}