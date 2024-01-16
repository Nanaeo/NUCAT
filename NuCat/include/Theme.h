#include "include/DirectoryReader.h"
#include <Windows.h>
#include <vector>
#include <string>
#include "yyjson.h"
// 写成类还是命名空间还是有待考虑
class Theme {
public:
	Theme(std::string ThemeName);
	~Theme();
	std::string GetInfoString();
	std::string SDKGetVersion();
	std::string SDKGetValue(std::string Key);
	std::string LanguageGetAll();
	std::string LanguageGet(std::string key);
	static std::string GetThemeEntry(std::string ThemeName);
	static std::vector<std::string> ListThemePathU8();
	static std::vector<std::wstring> ListThemePathW();
private:
	std::string _ThemeName;
	std::string retFileData;
	yyjson_val* ThemeJson;
	yyjson_doc* ThemeJsonRoot;
};