#include "include/DirectoryReader.h"
#include <Windows.h>
#include <vector>
#include <string>
class Theme {
public:
	Theme();
	~Theme();
	std::string GetThemeEntry(std::string ThemeName);
	std::vector<std::string> ListThemePathU8();
	std::vector<std::wstring> ListThemePathW(); 
private:
	DirectoryReader ThemeDictoryReader;
};