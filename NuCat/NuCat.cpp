#include "include/Header.h"
#include "include/NuCat.h"
#include "include/WMange.h"
#include "include/WindowMessage.h"
#include "include/EventHandler.h"
using namespace Microsoft::WRL;
int  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	//未安装Webview2
	if (!WebViewIsInstall()) {
		MessageBoxW(0,L"你未安装WebView2即将跳转下载",L"环境异常",0);
		ShellExecuteW(NULL, L"open", L"https://go.microsoft.com/fwlink/p/?LinkId=2124703", NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}
	//接下来创建默认窗口
	WMange window((long long*)&WndProc);
	window.Show();
	HWND hWnd = window.GetHandle();
	ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler** Handler = (ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler**)malloc(sizeof(ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler));
	if (Handler == nullptr) return 0;//avoid nullptr
	Handler = CreatHandler(hWnd);
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, *Handler);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
