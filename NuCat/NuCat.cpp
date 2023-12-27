#include <Windows.h>
#include "include/Language.h"
#include "include/Settings.h"
#include "include/Util.h"
int  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	Settings::Init();
	std::string LangConfig = Settings::GetKeyStr("Language", "zh-CN");
	if (LangConfig.compare("") == 0) {
		LangConfig.clear();
		LangConfig.append(GetConfigDefaultLocaleName());
	}
	Language::Init(LangConfig.c_str());
	//加载设置和多语言完成

	return 0;
}