#include "include/EventHandler.h"
#include "include/Log.h"
#include "include/Util.h"
#include "include/WinUi.h"
#include "include/Global.h"

HWND hwnd = CreatWindowUI();
webview::webview WebviewObject(true, &hwnd);
webview::webview* WebviewPtr = &WebviewObject;

void DefaultWindowBoot() {
	
	//设置到全局变量上
	WebviewObject.navigate(GetResourceU8((char*)u8"Resource\\index.html"));
	// 绑定退出函数
	WebviewObject.bind("exit", [&](const std::string&) -> std::string {
		exit(0);
		return "{}";
		});
	WebviewObject.run();

}
void EventHandler::Run(std::string action, std::string argv, int argc)
{
	//Log::Logging((char*)u8"",Log::LOG_DEBUG ); 日志测试
	action.pop_back(); // 去除判断干扰
	argv.pop_back();   // 去除判断干扰
	if (action.compare("") == 0 && argc == 0) {
		// 无参数正常启动 进入主页
		DefaultWindowBoot();
	}
	if (argc == 1 && action.compare("") != 0) {
		//拖动打开文件

	}
	// 其它带有命令行操作
}
