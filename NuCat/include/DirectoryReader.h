#pragma once
#include <windows.h>
#include <string>
#include <vector>

class DirectoryReader {
private:
    DWORD errorCode;

public:
    DirectoryReader();

    std::vector<std::wstring> getFilesList(const std::wstring& directoryPath);
    std::vector<std::wstring> getDirectoriesList(const std::wstring& directoryPath);
    DWORD getFileSize(const std::wstring& filePath);
    FILETIME getFileCreationTime(const std::wstring& filePath);
    DWORD GetObjectError();
};