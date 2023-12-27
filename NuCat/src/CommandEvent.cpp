#include "include/CommandEvent.h"
#include "include/NuCat.h"
#include "include/WMange.h"
#include "include/EventHandler.h"

bool DefaultWindowBoot() {
	WMange window((long long*)&WndProc, L"NuCat");
	window.Show();
	HWND hWnd = window.GetHandle();
	ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler** Handler = (ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler**)malloc(sizeof(ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler));
	if (Handler == nullptr) return 0;//avoid nullptr
	Handler = CreatHandler(hWnd);
	CreateCoreWebView2EnvironmentWithOptions(nullptr, GetResourcePath(L"\\WebViewData").c_str(), nullptr, *Handler);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}
//默认utf8编码
bool CommandEvent::EventRun(std::string action, std::string commandText, int argc)
{
	action.pop_back(); // 去除判断干扰
	if (action.compare("") == 0 && argc == 0) {
		// 无参数正常启动 进入主页
		DefaultWindowBoot();
	}
	if (argc == 1 && action.compare("") != 0) {
		//拖动打开文件
		
	}
	// 其它带有命令行操作
	return false;
}