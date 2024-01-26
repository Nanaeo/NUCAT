#include "include/LangFactory.h"

std::map<std::string, std::shared_ptr<Language>> LangFactory::instances_;

std::shared_ptr<Language> LangFactory::getInstance(const std::string& id, const std::wstring& langfile) {
	auto it = instances_.find(id);
	if (it == instances_.end()) {
		auto instance = std::make_shared<Language>(id, langfile);
		instances_[id] = instance;
		return instance;
	}
	else {
		return it->second;
	}
}

std::wstring LangFactory::GetMainFilePathW(std::string LocalName)
{
	std::wstring LocalNameU16 = Utf8ToUtf16(LocalName);
	std::wstring Local_PathU16 = L"\\Language\\" + LocalNameU16 + L".json";
	std::wstring Default_Path16 = L"\\Language\\zh-CN.json";

	std::wstring Local_Full_PathU16 = GetResourcePath(Local_PathU16.c_str());
	std::wstring Default_Full_PathU16 = GetResourcePath(Default_Path16.c_str());

	std::wstring Real_Full_PathU16 = (FileExists(Local_Full_PathU16.c_str()) ? Local_Full_PathU16.c_str() : Default_Full_PathU16.c_str());
	return Real_Full_PathU16;
}

std::wstring LangFactory::GetThemeFilePathW(std::string ThemeName, std::string LocalName)
{
	std::wstring LocalNameU16 = Utf8ToUtf16(LocalName);
	std::wstring ThemeNameU16 = Utf8ToUtf16(ThemeName);
	std::wstring Local_PathU16 = L"\\Resource\\Theme\\" + ThemeNameU16 + L"\\Language\\" + LocalNameU16 + L".json";
	std::wstring Default_Path16 = L"\\Resource\\Theme\\" + ThemeNameU16 + L"\\Language\\zh-CN.json";

	std::wstring Local_Full_PathU16 = GetResourcePath(Local_PathU16.c_str());
	std::wstring Default_Full_PathU16 = GetResourcePath(Default_Path16.c_str());

	std::wstring Real_Full_PathU16 = (FileExists(Local_Full_PathU16.c_str()) ? Local_Full_PathU16.c_str() : Default_Full_PathU16.c_str());
	return Real_Full_PathU16;
}