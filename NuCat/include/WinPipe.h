#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
class Pipe {
public:
    Pipe();
    ~Pipe();
    void Write(const wstring& data);
    wstring Read()();
private:
    HANDLE read_handle_;
    HANDLE write_handle_;
};
