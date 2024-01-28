// 管理主题
#include "include/DirectoryReader.h"
#include "include/FileOperator.h"
#include "include/Util.h"
#include "include/Theme.h"
//#include "include/Log.h" 不要在内部使用日志 外面用
#include <vector>
#include <algorithm>
#include <string>


Theme::Theme(std::string ThemeName)
{
	_ThemeName = ThemeName;
	std::wstring ThemeNameU16 = Utf8ToUtf16(ThemeName);
	std::wstring Local_PathU16 = L"\\Resource\\Theme\\" + ThemeNameU16 + L"\\package.json";
	std::wstring Default_Path16 = L"\\Resource\\Theme\\default\\package.json";
	std::wstring Local_Full_PathU16 = GetResourcePath(Local_PathU16.c_str());
	std::wstring Default_Full_PathU16 = GetResourcePath(Default_Path16.c_str());
	std::wstring Real_Full_PathU16 = (FileExists(Local_Full_PathU16.c_str()) ? Local_Full_PathU16.c_str() : Default_Full_PathU16.c_str());
	FileOperator ThemeFileOperator(Real_Full_PathU16.c_str());
	ThemeFileOperator.read(retFileData);
	ThemeJsonRoot = yyjson_read(retFileData.c_str(), retFileData.length(), 0);
	ThemeJson = yyjson_doc_get_root(ThemeJsonRoot);
}

Theme::~Theme()
{
	//暂时还没写回收资源
}

std::vector<std::wstring> Theme::ListThemePathW()
{
	DirectoryReader ThemeDictoryReader;
	std::vector<std::wstring> ThemeList = ThemeDictoryReader.getDirectoriesList(GetResourcePath(L"\\Resource\\Theme"));
	// ThemeList.erase(ThemeList.begin(), ThemeList.begin() + 2); 擦除不了 且性能消耗大 不如新建拷贝
	std::vector<std::wstring> RealThemeList(0);
	if (ThemeList.size() <= 2) return RealThemeList;
	//RealThemeList.resize(ThemeList.size() - 2);
	for (auto it = ThemeList.begin() + 2; it != ThemeList.end(); ++it) {
		RealThemeList.push_back(*it);
	}
	return RealThemeList;
}

std::vector<std::string> Theme::ListThemePathU8() {
	std::vector<std::wstring> ThemeList = Theme::ListThemePathW();
	std::vector<std::string> ThemeListU8;
	for (auto& TempElement : ThemeList) {
		ThemeListU8.push_back(Utf16ToUtf8(TempElement));
	}
	return ThemeListU8;
}					
		
std::string Theme::GetValueStr(const char* key, const char* errorText = nullptr)
{
	yyjson_val* Val = yyjson_obj_get(ThemeJson, key);
	if (Val == nullptr) {
		if (errorText == nullptr) return "";
		return errorText;
	}
	return yyjson_get_str(Val);
}
std::string Theme::GetThemeEntry(std::string ThemeName)
{
	std::string ThemeIndex = (char*)"\\Resource\\Theme\\" + ThemeName + (char*)"\\index.html";
	return GetResourcePathU8((char*)ThemeIndex.c_str());
}

std::string Theme::GetInfoString()
{
	return retFileData;
}

std::string Theme::SDKGetVersion()
{
	std::string ProtoVersion = this->GetValueStr((char*)u8"ProtoVersion", (char*)u8"1.0.0");
	if (ProtoVersion.compare("") == 0) return (char*)u8"1.0.0";
	return ProtoVersion;
}