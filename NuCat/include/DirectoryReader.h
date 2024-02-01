#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <string>
#include <vector>

class DirectoryReader {
public:
	DirectoryReader();
	static  std::vector<std::string> GetListFileU8(const std::wstring& _path);
	static  std::vector<std::string> GetListFileU8(const std::string& _path);
	static  void deleteAllFilesInDirectory(const std::wstring& directoryPath);
	static  std::vector<std::wstring> GetFilesList(const std::wstring& directoryPath);
	static  std::vector<std::wstring> GetDirectoriesList(const std::wstring& directoryPath);
	static  int GetFileSize(const std::wstring& filePath);
	static  std::string GetFileCreationTime(const std::wstring& filePath);
	static  std::vector<std::string> GetListPathU8(const std::string& _path);
	static  std::vector<std::string> GetListPathU8(const std::wstring& _path);
	static  std::vector<std::wstring> GetListPathW(const std::wstring& _path);
};