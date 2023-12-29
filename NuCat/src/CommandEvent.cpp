#include "include/CommandEvent.h"
#include "include/NuCat.h"
#include "include/WMange.h"
#include "include/webview.h"
bool DefaultWindowBoot() {
	webview::webview w(false, nullptr);
	w.set_title("Basic Example");
	w.set_size(480, 320, WEBVIEW_HINT_NONE);
	w.set_html("Thanks for using webview!");
	w.run();

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