#pragma
#include <string>
class Log {
public:
    enum LogLevel { DEBUG, INFO, WARNING, ERROR };
    Log(const std::string& filename, LogLevel level);
    void write(LogLevel level, const std::string& message);
    ~Log();

private:
    std::string filename_;
    FILE* file_;
    LogLevel level_;
};
