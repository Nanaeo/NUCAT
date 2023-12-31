#include "include/EventHandler.h"
#include "include/Log.h"
#include "include/Util.h"
#include "include/Global.h"
#include "include/Theme.h"
#include "include/WebBind.h"

webview::webview WebviewObject(true, nullptr);
HWND hwnd = (HWND)WebviewObject.window();
webview::webview* WebviewPtr = &WebviewObject;

void WindowBoot(std::string PageEntry) {
	SetWindowLongPtrW(hwnd, GWL_STYLE, WS_POPUP | WS_THICKFRAME);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
	//SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	//设置到全局变量上
	WebviewObject.navigate(PageEntry);


	// 绑定函数之后封装
	// 绑定退出函数
	WebviewObject.bind("exit", [&](const std::string&) -> std::string {
		exit(0);
		return "{}";
		});
	WebviewObject.bind("moveWindow", [&](const std::string&) -> std::string {
		SendMessageW(hwnd, WM_SYSCOMMAND, SC_MOVE, 0);
		// SendMessageW(hwnd, WM_SYSCOMMAND, SC_MOVE|HTCAPTION, 0);
		// SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt.x, pt.y));
		// 将就用吧反正找不到其它方案
		// SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
		return "{}";
		});
	// 绑定文件操作api
	WebviewObject.bind("NuCatListDirectory", [&](const std::string& req) -> std::string {
		DirectoryReader ListDictoryReader;
		std::string _Path = webview::detail::json_parse(req, "", 0);
		std::vector<std::string> ListPathData = ListDictoryReader.ListPathU8(_Path);
		std::string  retJson = WebBind::ListPathJsonU8(ListPathData);
		// Log::Logging(_Path,Log::LOG_ERROR); 测试完成u8编码
		// 获取文件路径
		// 调用本地方法 封装返回
		return retJson;
		});
	// WebviewObject.init("document.body.parentNode.style.overflowX = 'hidden'; ");
	WebviewPtr->resize_widget2();
	WebviewObject.run();

}
void EventHandler::Run(std::string action, std::string argv, int argc)
{
	//Log::Logging((char*)u8"",Log::LOG_DEBUG ); 日志测试
	action.pop_back(); // 去除判断干扰
	argv.pop_back();   // 去除判断干扰

	Theme ThemeMange;
	if (action.compare("") == 0 && argc == 0) {
		// 无参数正常启动 进入主页
		ThemeMange.ListThemePathW();
		std::string ThemeEntry = (char*)"file:\\\\\\" + ThemeMange.GetThemeEntry("default");
		WindowBoot(ThemeEntry);
	}
	if (argc == 1 && action.compare("") != 0) {
		//拖动打开文件 直接进入解压页面

	}
	// 其它带有命令行操作 包括命令行程序回传命令
}
