#pragma once
#include <map>
#include <memory>
#include <string>
#include "include/Theme.h"
class ThemeFactory {
public:
    static std::shared_ptr<Theme> getInstance(const std::string& ThemeName);
    static void SetCurrentTheme(const std::string& ThemeName);
    static std::shared_ptr<Theme> GetCurrentTheme();
private:
    ThemeFactory() = default;
    static std::string CurrentTheme;
    static std::map<std::string, std::shared_ptr<Theme>> instances_;
};
