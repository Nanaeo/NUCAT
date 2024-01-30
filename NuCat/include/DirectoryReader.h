#pragma once
#include <windows.h>
#include <string>
#include <vector>

class DirectoryReader {
private:

public:
	DirectoryReader();
	static std::vector<std::string> ListFileU8(std::wstring _path);
	static std::vector<std::string> ListFileU8(std::string _path);
	static void deleteAllFilesInDirectory(const std::wstring& directoryPath);
	static std::vector<std::wstring> getFilesList(const std::wstring& directoryPath);
	static  std::vector<std::wstring> getDirectoriesList(const std::wstring& directoryPath);
	static  DWORD getFileSize(const std::wstring& filePath);
	static  FILETIME getFileCreationTime(const std::wstring& filePath);
	static  std::vector<std::string> ListPathU8(std::string _path);
	static std::vector<std::string> ListPathU8(std::wstring _path);
	static  std::vector<std::wstring> ListPathW(std::wstring _path);
};