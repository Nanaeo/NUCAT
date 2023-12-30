#include "include/Log.h"
#include "include/Util.h"
#include "include/FileOperator.h"

int Log::CurrentLogLevel = 2; //WARN以上
void Log::SetLogLevel(int LogLevel)
{
	Log::CurrentLogLevel = LogLevel;
}
void Log::DeleteAll() {
	// 清除所有日志
}
void Log::SetOutHandler() {
	// 设置日志拦截
}
bool Log::Logging(std::string content, Level ErrorLevel)
{
	char* LogLevel[] = { (char*)u8"DEBUG", (char*)u8"INFO", (char*)u8"WARN", (char*)u8"ERROR", (char*)u8"EXIT" };
	std::string CurrentLogLevel = LogLevel[static_cast<int>(ErrorLevel)];
	if (static_cast<int>(ErrorLevel) < Log::CurrentLogLevel) {
		return false;
	}
	std::wstring CurrentDate = Utf8ToUtf16(getCurrentDate().c_str());
	CurrentDate.pop_back();
	std::wstring path = L"\\Log\\" + CurrentDate + L".txt";
	FileOperator LoggFile(GetResourcePath(path.c_str()).c_str());
	std::string RealConten;
	std::string  CurrentTimestamp = getCurrentDateTime();
	RealConten.append((char*)u8"[");
	RealConten.append(CurrentTimestamp);
	RealConten.append((char*)u8"] ");
	RealConten.append((char*)u8"[");
	RealConten.append(CurrentLogLevel);
	RealConten.append((char*)u8"] ");
	RealConten.append(content);
	RealConten.append("\n");
	LoggFile.append(RealConten.c_str());
	return true;
}
