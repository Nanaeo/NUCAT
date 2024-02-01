#pragma once
#include <string>
template <typename T>
class FileOperator {
public:
    FileOperator(const T& inFilePath);
    ~FileOperator();
    bool GetIsExists();
    bool ReadContent(std::string& content) const;
    bool WriteContent(const std::string& content);
    bool AppendContent(const std::string& content);
    bool RemoveFile();
private:
    T filePath;
};
template class FileOperator<std::wstring>;
template class FileOperator<std::string>;