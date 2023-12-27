#pragma once
#include <string>
namespace Log {
	enum Level
	{
		LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_EXIT
	};
	extern int CurrentLogLevel;
	void SetLogLevel(int LogLevel);
	bool Logging(std::string content, Level ErrorLevel);
}