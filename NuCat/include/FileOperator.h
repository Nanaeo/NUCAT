#pragma once
#include <string>
template <typename T>
class FileOperator {
public:
    FileOperator(const T& inFilePath);
    ~FileOperator() = default;
    bool GetIsExists();
    bool ReadContent(std::string& content);
    bool WriteContent(const std::string& content);
    bool AppendContent(const std::string& content);
    bool RemoveFile();
private:
    T filePath;
};