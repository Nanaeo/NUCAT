#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <string>
#include <vector>
template <typename T>
class DirectoryReader {
public:
	static  std::vector<std::string> GetListFileU8(const T& Path);
	static  std::vector<std::wstring> GetListFileW(const T& Path);
	static  std::vector<std::string> GetListPathU8(const T& Path);
	static  std::vector<std::wstring> GetListPathW(const T& Path);
	static  std::vector<std::string> GetListRelativeFileU8(const T& Path);
	static  std::vector<std::wstring> GetListRelativeFileW(const T& Path);
	static  std::vector<std::string> GetListRelativePathU8(const T& Path);
	static  std::vector<std::wstring> GetListRelativePathW(const T& Path);
	static  std::string GetFileCreationTime(const T& Path);
	static  bool RemovePathFiles(const T& Path);
	static  int GetFileSize(const T& filePath);
};

