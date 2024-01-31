#include "include/EventHandler.h"
#include "include/Log.h"
#include "include/DirectoryReader.h"
#include "include/Util.h"
#include "include/Global.h"
#include "include/Theme.h"
#include "include/WebBind.h"
#include "include/ThemeFactory.h"
#include "include/LangFactory.h"
#include <include/Bit7zWrapper.h>
webview::webview WebviewObject(true, nullptr);
HWND hwnd = (HWND)WebviewObject.window();
webview::webview* WebviewPtr = &WebviewObject;
void WindowBoot(std::string PageEntry) {
	SetWindowLongPtrW(hwnd, GWL_STYLE, WS_POPUP | WS_THICKFRAME);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	//SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
	//WebviewObject.init("alert(\"test\")");
	WebviewObject.navigate(PageEntry);
	//WebviewObject.eval("alert(\"test\")");

	// 目前大致分为5种 后期移动到webbind
	// window api
	WebviewObject.bind("NuCatExit", [&](const std::string&) -> std::string {
		exit(0);
		return "{}";
		});
	WebviewObject.bind("NuCatMoveWindow", [&](const std::string&) -> std::string {
		SendMessageW(hwnd, WM_SYSCOMMAND, SC_MOVE, 0);
		// SendMessageW(hwnd, WM_SYSCOMMAND, SC_MOVE|HTCAPTION, 0);
		// SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt.x, pt.y));
		// 将就用吧反正找不到其它方案
		// SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		return "{}";
		});
	// fs api 
	WebviewObject.bind("NuCatListDirectory", [&](const std::string& req) -> std::string {
		std::string _Path = webview::detail::json_parse(req, "", 0);
		std::vector<std::string> ListPathData = DirectoryReader::ListPathU8(Theme::GetThemeFile(RunTimeInfo["CurrentTheme"], _Path));
		std::string  retJson = WebBind::Vstring2Json(ListPathData);
		return retJson;
		});
	WebviewObject.bind("NuCatListFile", [&](const std::string& req) -> std::string {
		std::string _Path = webview::detail::json_parse(req, "", 0);
		std::vector<std::string> ListPathData = DirectoryReader::ListFileU8(Theme::GetThemeFile(RunTimeInfo["CurrentTheme"], _Path));
		std::string  retJson = WebBind::Vstring2Json(ListPathData);
		return retJson;
		});
	WebviewObject.bind("NuCatReadThemeFile", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatWriteThemeFile", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetThemeFilePath", [&](const std::string& req) -> std::string {
		return "";
		});
	// language api
	WebviewObject.bind("NuCatGetThemeLangAll", [&](const std::string& req) -> std::string {
		std::string GID = (char*)u8"Theme-" + RunTimeInfo["CurrentTheme"] + (char*)u8"-" + RunTimeInfo["CurrentLang"];
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(RunTimeInfo["CurrentTheme"], RunTimeInfo["CurrentLang"]));
		return Lang->getJsonAll();
		});
	WebviewObject.bind("NuCatGetThemeLang", [&](const std::string& req) -> std::string {
		std::string Key = webview::detail::json_parse(req, "", 0);
		std::string GID = (char*)u8"Theme-" + RunTimeInfo["CurrentTheme"] + (char*)u8"-" + RunTimeInfo["CurrentLang"];
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(RunTimeInfo["CurrentTheme"], RunTimeInfo["CurrentLang"]));
		return Lang->getStringValue(Key);
		});
	WebviewObject.bind("NuCatGetOtherThemeLangAll", [&](const std::string& req) -> std::string {
		std::string Theme = webview::detail::json_parse(req, "", 0);
		std::string GID = (char*)u8"Theme-" + Theme + (char*)u8"-" + RunTimeInfo["CurrentLang"];
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(RunTimeInfo["CurrentTheme"], RunTimeInfo["CurrentLang"]));
		return Lang->getJsonAll();
		});
	WebviewObject.bind("NuCatGetOtherThemeLang", [&](const std::string& req) -> std::string {
		std::string Theme = webview::detail::json_parse(req, "", 0);
		std::string Key = webview::detail::json_parse(req, "", 1);
		std::string GID = (char*)u8"Theme-" + Theme + (char*)u8"-" + RunTimeInfo["CurrentLang"];
		auto Lang = LangFactory::getInstance(GID, LangFactory::GetThemeFilePathW(RunTimeInfo["CurrentTheme"], RunTimeInfo["CurrentLang"]));
		return Lang->getStringValue(Key);
		});
	WebviewObject.bind("NuCatGetSysLang", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetSysLangAll", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetSettings", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatSetSettings", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGetSettingsAll", [&](const std::string& req) -> std::string {
		return "";
		});
	// helper api
	WebviewObject.bind("NuCatReboot", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGoUrl", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatGoUrlBack", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCatRegInit", [&](const std::string& req) -> std::string {
		return "";
		});
	// bit7z api
	WebviewObject.bind("NuCat7ZAutoExtract", [&](const std::string& req) -> std::string {
		std::string File = webview::detail::json_parse(req, "", 0);
		std::string OutPath = webview::detail::json_parse(req, "", 1);
		std::string Password = webview::detail::json_parse(req, "", 2);
		bool ret = Bit7zWrapper::Extract(File, OutPath, Bit7zWrapper::GetInformatE(getExtensionLowercaseU8(File)), Password);
		return WebBind::Bool2Json(ret);
		});
	WebviewObject.bind("NuCat7ZExtract", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZCommpressDirectory", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZAutoCommpressDirectory", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZGetArchiveInfo", [&](const std::string& req) -> std::string {
		return "";
		});
	WebviewObject.bind("NuCat7ZAutoGetArchiveInfo", [&](const std::string& req) -> std::string {
		return "";
		});

	WebviewPtr->resize_widget2();
	WebviewObject.run();

}
void EventHandler::Run(std::string action, std::string argv, int argc)
{
	// Log::Logging((char*)u8"",Log::LOG_DEBUG ); 日志测试
	RunTimeInfo["CurrentTheme"] = "default";
	Theme ThemeMange(RunTimeInfo["CurrentTheme"]);
	auto InfoTheme = ThemeMange.SDKGetVersion();
	//action.pop_back();
	if (action.compare("") == 0 && argc == 0) {
		// 无参数正常启动 进入主页
		std::string ThemeEntry = (char*)"file:\\\\\\" + Theme::GetThemeFile("default", "Test.html");
		WindowBoot(ThemeEntry);
	}
	if (argc == 1 && action.compare("") != 0) {
		//拖动打开文件 直接进入解压页面
		MessageBoxW(NULL, Utf8ToUtf16(argv).c_str(), L"", NULL);
		// #的方法无法传入信息 最好还是主动获取吧
		std::string ThemeEntry = (char*)"file:\\\\\\" + Theme::GetThemeEntry("default") + "#action=demo&path=" + argv;
		WindowBoot(ThemeEntry);

	}
	// 其它带有命令行操作 包括命令行程序回传命令
}
