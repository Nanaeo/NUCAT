#include "include/DirectoryReader.h"

DirectoryReader::DirectoryReader() : errorCode(ERROR_SUCCESS) {}

std::vector<std::wstring> DirectoryReader::getFilesList(const std::wstring& directoryPath) {
    std::vector<std::wstring> files;
    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW((directoryPath + L"\\*").c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        errorCode = GetLastError();
        return files;
    }
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            files.push_back(findData.cFileName);
        }
    } while (FindNextFileW(hFind, &findData));
    FindClose(hFind);
    return files;
}

std::vector<std::wstring> DirectoryReader::getDirectoriesList(const std::wstring& directoryPath) {
    std::vector<std::wstring> directories;
    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW((directoryPath + L"\\*").c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        errorCode = GetLastError();
        return directories;
    }
    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            directories.push_back(findData.cFileName);
        }
    } while (FindNextFileW(hFind, &findData));
    FindClose(hFind);
    return directories;
}

DWORD DirectoryReader::getFileSize(const std::wstring& filePath) {
    WIN32_FILE_ATTRIBUTE_DATA fileData;
    if (!GetFileAttributesExW(filePath.c_str(), GetFileExInfoStandard, &fileData)) {
        errorCode = GetLastError();
        return 0;
    }
    LARGE_INTEGER size;
    size.HighPart = fileData.nFileSizeHigh;
    size.LowPart = fileData.nFileSizeLow;
    return size.QuadPart;
}

FILETIME DirectoryReader::getFileCreationTime(const std::wstring& filePath) {
    WIN32_FILE_ATTRIBUTE_DATA fileData;
    if (!GetFileAttributesExW(filePath.c_str(), GetFileExInfoStandard, &fileData)) {
        errorCode = GetLastError();
        FILETIME ft = { 0, 0 };
        return ft;
    }
    return fileData.ftCreationTime;
}

DWORD DirectoryReader::GetObjectError() {
    return errorCode;
}
