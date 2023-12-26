#include "include/Header.h"
#include "include/NuCat.h"
#include "include/WMange.h"
#include "include/WindowMessage.h"
#include "include/EventHandler.h"
#include "bit7z/bit7z.hpp"
#include "include/NuSetting.h"

using namespace Microsoft::WRL;
wil::com_ptr<ICoreWebView2Controller> webviewController;
wil::com_ptr<ICoreWebView2> webview;
//加载全局设置到全局变量
NuSetting* NUCAT_SETTING = new NuSetting();

int  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	//载入多语言设置 未读取配置设置
	
	
	NuCatGetRealDefaultLocaleName();//utf8编码
	
	
	//设置 Utf8ToUtf16(buffer).c_str() 读取到设置文本UTF16内容
	//MessageBoxW(0, Utf8ToUtf16(buffer).c_str(), L"环境异常", 0);
	//未安装Webview2
	if (!WebViewIsInstall()) {
		MessageBoxW(0, L"你未安装WebView2即将跳转下载", L"环境异常", 0);
		ShellExecuteW(NULL, L"open", L"https://go.microsoft.com/fwlink/p/?LinkId=2124703", NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}
	//解析命令行
	int argc = 0;
	//如果不比较原始文本 会导致CommandLineToArgvW ARGV读取到本程序的地址
	if (!CompareWchatText(lpCmdLine, L"")) {
		LPWSTR* argv = CommandLineToArgvW(lpCmdLine, &argc);
		MessageBoxW(0, *argv, L"", 0);
	}

	//*argv 如果直接拖入文件 argv则为地址


	//读取7zip安装目录
	//MessageBoxW(0, Get7ZipInstallPath().c_str(), L"环境异常", 0);
	//测试bit7z
	//压缩代码已测

	/*using namespace bit7z;
	Bit7zLibrary lib("7z.dll");
	BitFileCompressor compressor{ lib, BitFormat::Zip };
	std::vector< std::string > files = { "F:\\NEWCPP\\NuCat\\out\\Pack\\NuCat.appx"};
	compressor.compress(files, "output_archive.zip");*/
	//WinPipe pipe;
	////pipe.SetUtf8();
	//MessageBoxW(0, Utf8ToUtf16(pipe.RunCommand(L"/c chcp 65001&&dir").c_str()).c_str(), L"", 0);
	//接下来创建默认窗口
	WMange window((long long*)&WndProc);
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
	return 0;
}
