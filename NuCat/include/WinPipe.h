#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
class Pipe {
public:
    Pipe();
    ~Pipe();
    SetUtf8();
    void Write(const string& data);
    string Read()();
private:
    HANDLE read_handle_;
    HANDLE write_handle_;
};
