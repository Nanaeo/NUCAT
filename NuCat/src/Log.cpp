#include "include/Log.h"
#include <ctime>

Log::Log(const std::string& filename, LogLevel level) : filename_(filename), level_(level) {
    //file_ = fopen(filename_.c_str(), "a");
}

void Log::write(LogLevel level, const std::string& message) {
    /*if (level >= level_) {
        time_t now = time(0);
        char* dt = ctime(&now);
        fprintf(file_, "%s %s: %s\n", dt, level == DEBUG ? "DEBUG" : level == INFO ? "INFO" : level == WARNING ? "WARNING" : "ERROR", message.c_str());
    }*/
}

Log::~Log() {
   /* fclose(file_);*/
}