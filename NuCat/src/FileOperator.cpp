#include "include/FileOperator.h"
FileOperator::FileOperator(const std::wstring& filePath) : filePath_(filePath), error_(ERROR_SUCCESS) {}

bool FileOperator::exists() {
    DWORD attr = GetFileAttributesW(filePath_.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        error_ = GetLastError();
        return false;
    }
    error_ = ERROR_SUCCESS;
    return true;
}

bool FileOperator::read(std::string& content) {
    HANDLE hFile = CreateFileW(filePath_.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        error_ = GetLastError();
        return false;
    }

    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        error_ = GetLastError();
        CloseHandle(hFile);
        return false;
    }

    char* buffer = new char[fileSize];
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, fileSize, &bytesRead, NULL)) {
        error_ = GetLastError();
        delete[] buffer;
        CloseHandle(hFile);
        return false;
    }

    content.assign(buffer, bytesRead);
    delete[] buffer;
    CloseHandle(hFile);
    error_ = ERROR_SUCCESS;
    return true;
}

bool FileOperator::write(const std::string& content) {
    HANDLE hFile = CreateFileW(filePath_.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        error_ = GetLastError();
        return false;
    }

    DWORD bytesWritten;
    if (!WriteFile(hFile, content.c_str(), content.size(), &bytesWritten, NULL)) {
        error_ = GetLastError();
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    error_ = ERROR_SUCCESS;
    return true;
}

bool FileOperator::append(const std::string& content) {
    HANDLE hFile = CreateFileW(filePath_.c_str(), FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        error_ = GetLastError();
        return false;
    }

    DWORD bytesWritten;
    if (!WriteFile(hFile, content.c_str(), content.size(), &bytesWritten, NULL)) {
        error_ = GetLastError();
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);
    error_ = ERROR_SUCCESS;
    return true;
}

bool FileOperator::remove() {
    if (!DeleteFileW(filePath_.c_str())) {
        error_ = GetLastError();
        return false;
    }

    error_ = ERROR_SUCCESS;
    return true;
}

DWORD FileOperator::getError() const {
    return error_;
}
