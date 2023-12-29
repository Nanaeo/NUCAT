#pragma once

// Copyright Mlikiowa 2023.12.27
// FileOperator针对Win32平台的文件操作封装 模块化完善
#include <string>
#include <windows.h>
class FileOperator {
public:
    FileOperator(const std::wstring& filePath);

    bool exists();
    bool read(std::string& content);
    bool write(const std::string& content);
    bool append(const std::string& content);
    bool remove();
    DWORD getError() const;

private:
    std::wstring filePath_;
    DWORD error_;
};
