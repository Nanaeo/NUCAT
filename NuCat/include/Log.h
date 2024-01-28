#pragma once
#include <string>
#include <functional>
namespace Log {
	enum Level
	{
		LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_EXIT
	};
	extern int CurrentLogLevel;
	void SetLogLevel(int LogLevel);
	void DeleteAll();
	void SetOutHandler(std::function<bool(std::string, Log::Level, std::string)> callback);
	bool Logging(std::string content, Level ErrorLevel);
	bool DefaultHandler(std::string content, Level ErrorLevel, std::string LogLevelStr);
}