#pragma once
#include <string>
namespace Log{
	enum Level
	{
		LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_EXIT
	};
	void SetLogLevel();
	void Logging(std::string content, Level ErrorLevel);
}