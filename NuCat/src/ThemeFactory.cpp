#include "include/ThemeFactory.h"

std::map<std::string, std::shared_ptr<Theme>> ThemeFactory::instances_;

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