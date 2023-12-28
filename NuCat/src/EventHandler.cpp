#include "include/EventHandler.h"
#include "include/Log.h"
#include "include/webview.h"
#include <include/Util.h>

void DefaultWindowBoot() {
	webview::webview w(true, nullptr);
	w.set_title("NUCAT");
	w.set_size(1050, 550, WEBVIEW_HINT_NONE);
	w.navigate(GetResourceU8((char*)u8"Resource\\index.html"));
	// 绑定退出函数
	w.bind("exit", [&](const std::string&) -> std::string {
		exit(0);
		return "{}";
		});
	w.run();

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
