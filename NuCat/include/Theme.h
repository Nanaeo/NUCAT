#include "include/DirectoryReader.h"
#include <Windows.h>
#include <vector>
#include <string>
// 写成类还是命名空间还是有待考虑
class Theme {
public:
	Theme();
	~Theme();
	std::string GetInfoString(std::string ThemeName);
	std::string GetThemeEntry(std::string ThemeName);
	std::vector<std::string> ListThemePathU8();
	std::vector<std::wstring> ListThemePathW(); 
	std::string LanguageGetAll(std::string ThemeName);
	std::string LanguageGet(std::string ThemeName,std::string key);
private:
	DirectoryReader ThemeDictoryReader;
};