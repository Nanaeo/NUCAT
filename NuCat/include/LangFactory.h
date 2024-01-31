#pragma once
#include <map>
#include <memory>
#include <string>
#include "include/Language.h"

class LangFactory {
public:
    static std::shared_ptr<Language> getInstance(const std::string& id, const std::wstring& langfile);
    static std::wstring GetMainFilePathW(std::string LocalName);
    static std::wstring GetThemeFilePathW(std::string ThemeName, std::string LocalName);
    std::shared_ptr<Language> GetCurrentSysInstance();
private:
    LangFactory() = default;

    static std::map<std::string, std::shared_ptr<Language>> instances_;
};
