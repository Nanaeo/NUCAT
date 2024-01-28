#pragma once
#include <windows.h>
#include <string>
#include <vector>

class DirectoryReader {
private:
    DWORD errorCode;

public:
    DirectoryReader();
    void deleteAllFilesInDirectory(const std::wstring& directoryPath);
    std::vector<std::wstring> getFilesList(const std::wstring& directoryPath);
    std::vector<std::wstring> getDirectoriesList(const std::wstring& directoryPath);
    DWORD getFileSize(const std::wstring& filePath);
    FILETIME getFileCreationTime(const std::wstring& filePath);
    DWORD GetObjectError();
    std::vector<std::string> ListPathU8(std::string _path);
    std::vector<std::string> ListPathU8(std::wstring _path);
    std::vector<std::wstring> ListPathW(std::wstring _path);
};