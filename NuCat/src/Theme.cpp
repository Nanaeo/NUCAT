// 管理主题
#include "include/DirectoryReader.h"
#include "include/Util.h"
#include "include/Theme.h"
//#include "include/Log.h" 不要在内部使用日志 外面用
#include <vector>
#include <algorithm>
#include <string>

Theme::Theme()
{
}

Theme::~Theme()
{
}
std::vector<std::wstring> Theme::ListThemePathW()
{
	std::vector<std::wstring> ThemeList = ThemeDictoryReader.getDirectoriesList(GetResourcePath(L"\\Resource\\Theme"));
	// ThemeList.erase(ThemeList.begin(), ThemeList.begin() + 2); 擦除不断 性能消耗大 不如新建拷贝
	std::vector<std::wstring> RealThemeList(0);
	if (ThemeList.size() <= 2) return RealThemeList;
	//RealThemeList.resize(ThemeList.size() - 2);
	for (auto it = ThemeList.begin() + 2; it != ThemeList.end(); ++it) {
		RealThemeList.push_back(*it);
	}
	return RealThemeList;
}

std::vector<std::string> Theme::ListThemePathU8() {
	std::vector<std::wstring> ThemeList = this->ListThemePathW();
	std::vector<std::string> ThemeListU8;
	for (auto& TempElement : ThemeList) {
		ThemeListU8.push_back(Utf16ToUtf8(TempElement));
	}
	return ThemeListU8;
}
std::string Theme::GetThemeEntry(std::string ThemeName)
{
	std::string ThemeIndex = (char*)"\\Resource\\Theme\\" + ThemeName + (char *)"\\index.html";
	return GetResourcePathU8((char *)ThemeIndex.c_str());
}
