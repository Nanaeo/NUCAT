#include "include/DirectoryReader.h"
#include "include/Util.h"

DirectoryReader::DirectoryReader() {}
std::vector<std::string> DirectoryReader::GetListFileU8(const std::wstring& _path) {
	std::vector<std::string> FileListU8;
	for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		auto ret = entry.path().u8string();
		FileListU8.push_back(std::string(ret.begin(), ret.end()));
	}
	return FileListU8;
}
std::vector<std::string> DirectoryReader::GetListFileU8(const std::string& _path) {
	std::wstring pathW = Utf8ToUtf16(_path);
	return DirectoryReader::GetListFileU8(pathW);
}
void DirectoryReader::deleteAllFilesInDirectory(const std::wstring& directoryPath) {
	for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
		if (entry.is_directory()) {
			std::filesystem::remove_all(entry.path());
		}
		else {
			std::filesystem::remove(entry.path());
		}
	}
}
std::vector<std::wstring> DirectoryReader::GetFilesList(const std::wstring& directoryPath) {
	std::vector<std::wstring> files;
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
		if (entry.is_regular_file()) {
			files.push_back(entry.path().wstring());
		}
	}
	return files;
}

std::vector<std::wstring> DirectoryReader::GetDirectoriesList(const std::wstring& directoryPath) {
	std::vector<std::wstring> directories;
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
		if (entry.is_directory()) {
			directories.push_back(entry.path().wstring());
		}
	}
	return directories;
}
int DirectoryReader::GetFileSize(const std::wstring& filePath) {
	return static_cast<int>(std::filesystem::file_size(filePath));
}

std::string DirectoryReader::GetFileCreationTime(const std::wstring& filePath) {
	auto time = std::filesystem::last_write_time(filePath);
	auto duration = time.time_since_epoch();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
	return std::to_string(seconds);
}


std::vector<std::string> DirectoryReader::GetListPathU8(const std::string& _path) {
	std::wstring pathW = Utf8ToUtf16(_path);
	return DirectoryReader::GetListPathU8(pathW);
}

std::vector<std::string> DirectoryReader::GetListPathU8(const std::wstring& _path) {
	std::vector<std::wstring> PathList = DirectoryReader::GetListPathW(_path);
	std::vector<std::string> PathListU8;
	for (const auto& TempElement : PathList) {
		PathListU8.push_back(Utf16ToUtf8(TempElement));
	}
	return PathListU8;
}

std::vector<std::wstring> DirectoryReader::GetListPathW(const std::wstring& _path) {
	std::vector<std::wstring> RealThemeList;
	for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		if (entry.is_directory()) {
			RealThemeList.push_back(entry.path().wstring());
		}
	}
	return RealThemeList;
}