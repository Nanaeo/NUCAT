#include "include/DirectoryReader.h"
#include <Windows.h>
#include <vector>
#include <string>
class Theme {
public:
	Theme();
	~Theme();
	std::string GetInfo(std::string ThemeName);
	std::string GetThemeEntry(std::string ThemeName);
	std::vector<std::string> ListThemePathU8();
	std::vector<std::wstring> ListThemePathW(); 
	std::string LanguageGetAll(std::string ThemeName);
	std::string LanguageGet(std::string ThemeName,std::string key);
private:
	DirectoryReader ThemeDictoryReader;
};