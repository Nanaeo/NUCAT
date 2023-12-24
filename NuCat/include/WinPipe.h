#pragma once
#include <windows.h>
#include <string>

class WinPipe {
public:
    WinPipe();
    ~WinPipe();
    std::string RunCommand(const std::wstring& command);
    void SetUtf8();
private:
    HANDLE read_handle_;
    HANDLE write_handle_;
};
