#include "include/Settings.h"
#include "include/Util.h"
Settings* Settings::instance = nullptr;
std::string  Settings::GetThemeU8()
{

	std::string DefaultTheme = getStringValue((char*)u8"Theme", (char*)u8"default");
	if (DefaultTheme.compare("") == 0) return (char*)u8"default";
	return DefaultTheme;
}

std::wstring  Settings::GetThemeW() {
	std::wstring DefaultTheme = Utf8ToUtf16(Settings::GetThemeU8());
	return DefaultTheme;
}

Settings::Settings() :JsonReader(GetResourcePath(L"\\Config\\Settings.json")) {}

Settings::~Settings()
{
}
Settings* Settings::getInstance() {
	if (instance == nullptr) {
		instance = new Settings();
	}
	return instance;
}