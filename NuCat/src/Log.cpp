#include "include/Log.h"
#include "include/FileOperator.h"
#include "include/Util.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string getCurrentDate() {
	auto now = std::chrono::system_clock::now();
	auto nowTime = std::chrono::system_clock::to_time_t(now);
	std::tm* tmNow = std::localtime(&nowTime);
	std::ostringstream oss;
	oss << std::put_time(tmNow, "%Y-%m-%d");
	return oss.str();
}
std::string getCurrentTimestamp() {
	// 获取当前时间点
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	// 创建一个输出字符串流
	std::ostringstream oss;
	oss << millis;
	return oss.str();
}
void Log::SetLogLevel()
{
}

void Log::Logging(std::string content, Level ErrorLevel)
{
	char* LogLevel[] = { (char*)u8"DEBUG", (char*)u8"INFO", (char*)u8"WARN", (char*)u8"ERROR", (char*)u8"EXIT" };
	std::string CurrentLogLevel = LogLevel[static_cast<int>(ErrorLevel)];
	std::wstring CurrentDate = Utf8ToUtf16(getCurrentDate().c_str());
	CurrentDate.pop_back();
	std::wstring path = L"\\Log\\" + CurrentDate + L".txt";
	FileOperator LoggFile(GetResourcePath(path.c_str()).c_str());
	std::string RealConten;
	std::string  CurrentTimestamp = getCurrentTimestamp();
	RealConten.append((char*)u8"[");
	RealConten.append(CurrentTimestamp);
	RealConten.append((char*)u8"] ");
	RealConten.append((char*)u8"[");
	RealConten.append(CurrentLogLevel);
	RealConten.append((char*)u8"] ");
	RealConten.append(content);
	RealConten.append("\n");
	LoggFile.append(RealConten.c_str());
}
