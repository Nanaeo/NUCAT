#include "include/NuSetting.h"
#include "include/Util.h"
#include "include/FileOperator.h"

NuSetting::NuSetting()
{
	std::wstring SettingPath = GetResourcePath(L"\\Config\\Settings.json");
	FileOperator SettingFileOperator(SettingPath.c_str());
	std::string retFileData;
	SettingFileOperator.read(retFileData);
	
	SettingJsonRoot = yyjson_read(retFileData.c_str(), retFileData.length(), 0);
	SettingJson = yyjson_doc_get_root(SettingJsonRoot);
}

NuSetting::~NuSetting()
{
	yyjson_doc_free(SettingJsonRoot);

}

std::string NuSetting::GetKeyStr(const char* key)
{
	yyjson_val* Val = yyjson_obj_get(SettingJson, key);
	if (Val == nullptr) {
		std::string ErrorText((const char*)u8"");
		return ErrorText;
	}
	return yyjson_get_str(Val);
}

void NuSetting::SetKey()
{

}