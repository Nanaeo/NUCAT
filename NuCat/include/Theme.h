#include "include/DirectoryReader.h"
#include <Windows.h>
#include <vector>
#include <string>
class Theme {
public:
	Theme();
	~Theme();
	std::vector<std::wstring> ListThemePathW();
private:
	DirectoryReader ThemeDictoryReader;
};