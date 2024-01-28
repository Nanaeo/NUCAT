#include "include/Log.h"
#include "include/Util.h"
#include "include/FileOperator.h"
#include "include/DirectoryReader.h"
std::function<bool(std::string, Log::Level, std::string)> HandlerFunction = Log::DefaultHandler;

int Log::CurrentLogLevel = 2; //WARN以上
void Log::SetLogLevel(int LogLevel)
{
	Log::CurrentLogLevel = LogLevel;
}
void Log::DeleteAll() {
	// 清除所有日志 直接清空整个日志目录
	DirectoryReader Reader;
	Reader.deleteAllFilesInDirectory(GetResourcePath(L"\\Log\\"));
}
void Log::SetOutHandler(std::function<bool(std::string, Log::Level, std::string)> callback) {
	HandlerFunction = callback;
	// 设置日志拦截 通过注册回调函数
}
bool Log::Logging(std::string content, Level ErrorLevel)
{
	if (static_cast<int>(ErrorLevel) < Level::LOG_DEBUG || static_cast<int>(ErrorLevel) > Level::LOG_EXIT) {
		return false;
	}
	// 过滤无效等级日志
	if (static_cast<int>(ErrorLevel) < Log::CurrentLogLevel) {
		return false;
	}
	// 过滤低等级日志
	char* LogLevel[] = { (char*)u8"DEBUG", (char*)u8"INFO", (char*)u8"WARN", (char*)u8"ERROR", (char*)u8"EXIT" };
	std::string LogLevelStr = LogLevel[static_cast<int>(ErrorLevel)];
	return HandlerFunction(content, ErrorLevel, LogLevelStr);
}

bool Log::DefaultHandler(std::string Content, Level ErrorLevel, std::string LogLevelStr)
{
	std::wstring CurrentDate = Utf8ToUtf16(getCurrentDate().c_str());
	std::wstring path = L"\\Log\\" + CurrentDate + L".txt";
	FileOperator LoggFile(GetResourcePath(path.c_str()).c_str());
	std::string RealConten;
	std::string  CurrentTimestamp = getCurrentDateTime();
	RealConten.append((char*)u8"[");
	RealConten.append(CurrentTimestamp);
	RealConten.append((char*)u8"] ");
	RealConten.append((char*)u8"[");
	RealConten.append(LogLevelStr);
	RealConten.append((char*)u8"] ");
	RealConten.append(Content);
	RealConten.append("\n");
	LoggFile.append(RealConten.c_str());
	return true;
}
