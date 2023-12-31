#include "include/DirectoryReader.h"
#include "include/Util.h"

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
    //DWORD 一般超不出 超出了就是不合理的
    return (DWORD)size.QuadPart;
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

std::vector<std::string> DirectoryReader::ListPathU8(std::string _path)
{
    std::wstring pathW = Utf8ToUtf16(_path);
    return this->ListPathU8(pathW);
}

std::vector<std::string> DirectoryReader::ListPathU8(std::wstring _path) {
    std::vector<std::wstring> PathList = this->ListPathW(_path);
    std::vector<std::string> PathListU8;
    for (auto& TempElement : PathList) {
        PathListU8.push_back(Utf16ToUtf8(TempElement));
    }
    return PathListU8;
}

std::vector<std::wstring> DirectoryReader::ListPathW(std::wstring _path)
{
    _path.pop_back();//转出来多了\0 这个问题大量存在
    std::vector<std::wstring> ThemeList = this->getDirectoriesList(_path);
    // ThemeList.erase(ThemeList.begin(), ThemeList.begin() + 2); 擦除不断 性能消耗大 不如新建拷贝
    std::vector<std::wstring> RealThemeList(0);
    if (ThemeList.size() <= 2) return RealThemeList;
    //RealThemeList.resize(ThemeList.size() - 2);
    for (auto it = ThemeList.begin() + 2; it != ThemeList.end(); ++it) {
        RealThemeList.push_back(*it);
    }
    return RealThemeList;
}
