#pragma once
#include <map>
#include <memory>
#include <string>
#include "include/Theme.h"
class ThemeFactory {
public:
    static std::shared_ptr<Theme> getInstance(const std::string& ThemeName);
private:
    ThemeFactory() = default;
    static std::map<std::string, std::shared_ptr<Theme>> instances_;
};
