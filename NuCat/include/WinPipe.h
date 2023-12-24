#pragma once
#include <windows.h>
#include <string>

class WinPipe {
public:
    WinPipe();
    ~WinPipe();
    std::string RunCommand(const std::string& command);
    void SetUtf8();
private:
    HANDLE read_handle_;
    HANDLE write_handle_;
};
