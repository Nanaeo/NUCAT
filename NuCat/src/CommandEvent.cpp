#include "include/CommandEvent.h"

//默认utf8编码
bool CommandEvent::EventRun(std::string action, std::string commandText, int argc)
{
	if (action == (char *)u8"" && argc == 0) {
		// 无参数正常启动
	}
	if (argc == 1 && action != (char*)u8"") {
		//拖动打开文件
	}
	// 其它带有命令行操作
	return false;
}