#include "include/Header.h"
#include "include/NuCat.h"
#include "include/WMange.h"
#include "include/WindowMessage.h"
#include "bit7z/bit7z.hpp"
#include "include/NuSetting.h"
#include "include/NuVersion.h"
#include "include/CommandEvent.h"


using namespace Microsoft::WRL;
wil::com_ptr<ICoreWebView2Controller> webviewController;
wil::com_ptr<ICoreWebView2> webview;


//加载全局设置到全局变量
NuSetting* NUCAT_SETTING = new NuSetting();
//加载语言包
NuLanguage* NUCAT_LANG = new NuLanguage(NuCatGetRealDefaultLocaleName());

int  wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {
	NuVersion::Init();
	//Log::Logging("Message",Log::Level::LOG_DEBUG);
	// std::string CurremtVersion = NuVersion::FullVersion; 快速获取版本信息
	// 环境检查-未安装Webview2
	if (!WebViewIsInstall()) {
		MessageBoxW(0, NUCAT_LANG->TextW("WebView_NotInstall_Content").c_str(), NUCAT_LANG->TextW("WebView_NotInstall_Tittle").c_str(), 0);
		ShellExecuteW(NULL, L"open", L"https://go.microsoft.com/fwlink/p/?LinkId=2124703", NULL, NULL, SW_SHOWNORMAL);
		return 0;
	}
	// 环境检查-现在没必要读取7zip安装目录因为7z.dll我们已经默认包括在项目 Get7ZipInstallPath()
	
	// 事件处理-解析命令行
	int argc = 0;
	// 设置argv默认值
	std::wstring argvDefaultWSTR(L"");
	LPWSTR argvDefaultLPWSTR = (LPWSTR)argvDefaultWSTR.c_str();
	LPWSTR* argv = &argvDefaultLPWSTR;
	// 如果不比较原始文本 会导致CommandLineToArgvW ARGV读取到本程序的地址
	if (!CompareWchatText(lpCmdLine, L"")) {
		argv = CommandLineToArgvW(lpCmdLine, &argc);
	}
	bool ret_CommandEvent = CommandEvent::EventRun(Utf16ToUtf8(*argv), Utf16ToUtf8(lpCmdLine), argc);
	return 0;
}
