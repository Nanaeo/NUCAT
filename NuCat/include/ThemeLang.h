#pragma once
#include <Windows.h>
#include <string>
#include "include/yyjson.h"
class ThemeLang
{
public:
	ThemeLang(std::string ThemeName,std::string LocalName);
	~ThemeLang();
	std::string ThemeLang::LanguageGet(std::string key);
	std::string ThemeLang::LanguageGetAll();

private:
	yyjson_val* LanguageJson;
	yyjson_doc* LanguageJsonRoot;
	std::string retFileData;
};
// 关于为什么拆开 是因为ThemeLang需要多例 数量多余Theme类 同时不能伴生Theme 同时肯定也不能设计成Language一样的namespace隔开
// 所以拆开是最好的方式 但是代码服用率低 Language Setting Theme 都存在大量重复代码 后期重构可用考虑继承一个类完成 相同部分 读取json 读取值 设置值 回收资源 进一步封装