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
	std::string GetValueStr(const char* key, const char* errorText);
	std::string LanguageGetAll();
	std::string LanguageGet(std::string key);
	static std::string GetThemeEntry(std::string ThemeName);
	static std::vector<std::string> ListThemePathU8();
	static std::vector<std::wstring> ListThemePathW();
private:
	yyjson_val* ThemeLanguageJson;
	yyjson_doc* ThemeLanguageJsonRoot;
	std::string _ThemeName;
	std::string retFileData;
	yyjson_val* ThemeJson;
	yyjson_doc* ThemeJsonRoot;
};