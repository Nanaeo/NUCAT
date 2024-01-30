#include "include/DirectoryReader.h"
#include "include/Util.h"

DirectoryReader::DirectoryReader() {}
std::vector<std::string> DirectoryReader::ListFileU8(std::wstring _path) {
	std::vector<std::wstring> FileList = DirectoryReader::getFilesList(_path);
	std::vector<std::string> FileListU8;
	for (auto& TempElement : FileList) {
		auto test = Utf16ToUtf8(TempElement);
		FileListU8.push_back(test);
	}
	return FileListU8;
}
std::vector<std::string> DirectoryReader::ListFileU8(std::string _path)
{
	std::wstring pathW = Utf8ToUtf16(_path);
	return DirectoryReader::ListFileU8(pathW);
}

void DirectoryReader::deleteAllFilesInDirectory(const std::wstring& directoryPath)
{
	WIN32_FIND_DATAW findData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	std::wstring filePath = directoryPath + L"\\*";
	hFind = FindFirstFileW(filePath.c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE) {
		return;
	}
	do {
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (wcscmp(findData.cFileName, L".") != 0 && wcscmp(findData.cFileName, L"..") != 0) {
				std::wstring subDirectoryPath = directoryPath + L"\\" + findData.cFileName;
				deleteAllFilesInDirectory(subDirectoryPath);
				RemoveDirectoryW(subDirectoryPath.c_str());
			}
		}
		else {
			std::wstring filePath = directoryPath + L"\\" + findData.cFileName;
			DeleteFileW(filePath.c_str());
		}
	} while (FindNextFileW(hFind, &findData) != 0);
	FindClose(hFind);
}

std::vector<std::wstring> DirectoryReader::getFilesList(const std::wstring& directoryPath) {
	std::vector<std::wstring> files;
	WIN32_FIND_DATAW findData;
	HANDLE hFind = FindFirstFileW((directoryPath + L"\\*").c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE) {
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
		FILETIME ft = { 0, 0 };
		return ft;
	}
	return fileData.ftCreationTime;
}

std::vector<std::string> DirectoryReader::ListPathU8(std::string _path)
{
	std::wstring pathW = Utf8ToUtf16(_path);
	return DirectoryReader::ListPathU8(pathW);
}

std::vector<std::string> DirectoryReader::ListPathU8(std::wstring _path) {
	std::vector<std::wstring> PathList = DirectoryReader::ListPathW(_path);
	std::vector<std::string> PathListU8;
	for (auto& TempElement : PathList) {
		auto test = Utf16ToUtf8(TempElement);
		PathListU8.push_back(test);
	}
	return PathListU8;
}

std::vector<std::wstring> DirectoryReader::ListPathW(std::wstring _path)
{
	std::vector<std::wstring> ThemeList = DirectoryReader::getDirectoriesList(_path);
	// ThemeList.erase(ThemeList.begin(), ThemeList.begin() + 2); 擦除不了 性能消耗大 不如新建拷贝
	std::vector<std::wstring> RealThemeList(0);
	if (ThemeList.size() <= 2) return RealThemeList;
	//RealThemeList.resize(ThemeList.size() - 2);
	for (auto it = ThemeList.begin() + 2; it != ThemeList.end(); ++it) {
		RealThemeList.push_back(*it);
	}
	return RealThemeList;
}
