#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
class Pipe {
public:
    Pipe();
    ~Pipe();
    void SetUtf8();
    void Write(const std::string& data);
    std::string Read();
    HANDLE GetReadHandle() const;
    HANDLE GetWriteHandle() const;
private:
    HANDLE read_handle_;
    HANDLE write_handle_;
};
