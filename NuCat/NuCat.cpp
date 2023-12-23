#include "include/Header.h"
#include "include/NuCat.h"
#include "include/WMange.h"
#include "include/WindowMessage.h"
#include "include/EventHandler.h"
using namespace Microsoft::WRL;

int  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	WMange window((long long*)&WndProc);
	window.Show();
	HWND hWnd = window.GetHandle();
	ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler** Handler = (ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler**)malloc(sizeof(ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler));
	if (Handler == nullptr) {
		exit(0);
	}
	Handler = CreatHandler(hWnd);
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr, *Handler);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
