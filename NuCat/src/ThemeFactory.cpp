#include "include/ThemeFactory.h"

std::map<std::string, std::shared_ptr<Theme>> ThemeFactory::instances_;
std::string ThemeFactory::CurrentTheme = "";
std::shared_ptr<Theme> ThemeFactory::getInstance(const std::string& ThemeName) {
	auto it = instances_.find(ThemeName);
	if (it == instances_.end()) {
		auto instance = std::make_shared<Theme>(ThemeName);
		instances_[ThemeName] = instance;
		return instance;
	}
	else {
		return it->second;
	}
}
void ThemeFactory::SetCurrentTheme(const std::string& ThemeName) {
	CurrentTheme = ThemeName;
}
std::shared_ptr<Theme> ThemeFactory::GetCurrentTheme() {
	auto it = instances_.find(CurrentTheme);
	if (it == instances_.end()) {
		return nullptr;
	}
	else {
		return it->second;
	}
}