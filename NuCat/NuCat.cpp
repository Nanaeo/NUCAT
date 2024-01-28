﻿#include "include/Log.h"
#include "include/LangFactory.h"
#include "include/Settings.h"
#include "include/Util.h"
#include "include/Webview2Tool.h"
#include "include/EventHandler.h"

int  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	// 初始化版本信息
	Settings::Init();
	// 初始化设置
	std::string LangConfig = Settings::GetKeyStr("Language", "zh-CN");
	if (LangConfig.compare("") == 0) {
		LangConfig.clear();
		LangConfig.append(GetConfigDefaultLocaleName());
	}
	Log::SetLogLevel(std::stoi(Settings::GetKeyStr("LogLevel", "2")));
	// 设置错误输出等级
	auto Lang = LangFactory::getInstance("System", LangFactory::GetMainFilePathW(LangConfig));
	// 加载多语言
	if (!WebViewIsInstall()) {
		MessageBoxW(0, Lang->TextW("WebView_NotInstall_Content").c_str(), Lang->TextW("WebView_NotInstall_Tittle").c_str(), 0);
		ShellExecuteW(NULL, L"open", Lang->TextW("WebView_NotInstall_Downlod").c_str(), NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}
	// 判断Webview2 Environment
	int argc = 0;
	// 设置argv默认值
	std::wstring argvDefaultWSTR(L"");
	LPWSTR argvDefaultLPWSTR = (LPWSTR)argvDefaultWSTR.c_str();
	LPWSTR* argv = &argvDefaultLPWSTR;
	// 如果不比较原始文本 会导致CommandLineToArgvW ARGV读取到本程序的地址
	if (!CompareWchatText(lpCmdLine, L"")) {
		argv = CommandLineToArgvW(lpCmdLine, &argc);
	}
	EventHandler::Run(Utf16ToUtf8(*argv), Utf16ToUtf8(lpCmdLine), argc);
	// Bit7zWrapper::Extract((char*)u8"F:\\CPPDEV\\测试.zip", (char *)u8"F:\\CPPDEV\\测试\\", bit7z::BitFormat::Zip, "");
	return 0;
}