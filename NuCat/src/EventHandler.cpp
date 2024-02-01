#include "include/EventHandler.h"
#include "include/Log.h"
#include "include/DirectoryReader.h"
#include "include/Util.h"
#include "include/Global.h"
#include "include/WebBind.h"
#include "include/ThemeFactory.h"
#include "include/LangFactory.h"
#include <include/Settings.h>
webview::webview WebviewObject(true, nullptr);
HWND WebViewHwnd = (HWND)WebviewObject.window();
void WindowBoot(std::string PageEntry) {
	SetWindowLongPtrW(WebViewHwnd, GWL_STYLE, WS_POPUP | WS_THICKFRAME);
	SetWindowPos(WebViewHwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	//SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
	//WebviewObject.init("alert(\"test\")");
	WebviewObject.navigate(PageEntry);
	//WebviewObject.eval("alert(\"test\")");
	WebBind::RegJsBridge();
	WebviewObject.resize_widget2();
	WebviewObject.run();

}
void EventHandler::Run(std::string action, std::string argv, int argc)
{
	auto SysSettings = Settings::getInstance();
	std::string CurrentTheme = SysSettings->getStringValue("Theme", "default");
	auto ThemeInstance = ThemeFactory::getInstance(CurrentTheme);//初始化
	ThemeFactory::SetCurrentTheme(CurrentTheme);//设置标识
	if (action.compare("") == 0 && argc == 0) {
		// 无参数正常启动 进入主页
		std::string ThemeEntry = (char*)"file:\\\\\\" + ThemeInstance->GetThemeFile("Test.html");
		WindowBoot(ThemeEntry);
	}
	if (argc == 1 && action.compare("") != 0) {
		//拖动打开文件 直接进入解压页面
		MessageBoxW(NULL, Utf8ToUtf16(argv).c_str(), L"", NULL);
		// #的方法无法传入信息 最好还是主动获取吧
		std::string ThemeEntry = (char*)"file:\\\\\\" + ThemeInstance->GetThemeEntry();
		WindowBoot(ThemeEntry);

	}
	// 其它带有命令行操作 包括命令行程序回传命令
}
