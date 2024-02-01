#include "include/DirectoryReader.h"
#include "include/Util.h"

template<>
std::vector<std::string> DirectoryReader<std::wstring>::GetListFileU8(const std::wstring& _path) {
	std::vector<std::string> FileListU8;
	for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		auto ret = entry.path().u8string();
		FileListU8.push_back(std::string(ret.begin(), ret.end()));
	}
	return FileListU8;
}
template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListFileU8(const std::wstring& _path) {
	return std::vector<std::string>();
}
template<>
std::vector<std::string> DirectoryReader<std::string>::GetListFileU8(const std::string& _path) {
	std::wstring pathW = Utf8ToUtf16(_path);
	return DirectoryReader<std::wstring>::GetListFileU8(pathW);
}
template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListFileU8(const std::string& _path) {
	return std::vector<std::string>();
}

template<>
void DirectoryReader<std::wstring>::DeleteAllFilesInDirectory(const std::wstring& directoryPath) {
	for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
		if (entry.is_directory()) {
			std::filesystem::remove_all(entry.path());
		}
		else {
			std::filesystem::remove(entry.path());
		}
	}
}
template<typename T>
void DirectoryReader<T>::DeleteAllFilesInDirectory(const std::wstring& directoryPath) {
}
template<>
std::vector<std::wstring> DirectoryReader<std::wstring>::GetFilesList(const std::wstring& directoryPath) {
	std::vector<std::wstring> files;
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
		if (entry.is_regular_file()) {
			files.push_back(entry.path().wstring());
		}
	}
	return files;
}
template<typename T>
std::vector<std::wstring> DirectoryReader<T>::GetFilesList(const std::wstring& directoryPath) {
	return std::vector<std::wstring>();
}
template<>
std::vector<std::wstring> DirectoryReader<std::wstring>::GetDirectoriesList(const std::wstring& directoryPath) {
	std::vector<std::wstring> directories;
	for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
		if (entry.is_directory()) {
			directories.push_back(entry.path().wstring());
		}
	}
	return directories;
}
template<typename T>
std::vector<std::wstring> DirectoryReader<T>::GetDirectoriesList(const std::wstring& directoryPath) {
	return std::vector<std::wstring>();
}
template<>
int DirectoryReader<std::wstring>::GetFileSize(const std::wstring& filePath) {
	return static_cast<int>(std::filesystem::file_size(filePath));
}
template<typename T>
int DirectoryReader<T>::GetFileSize(const std::wstring& filePath) {
	return 0;
}
template<>
std::string DirectoryReader<std::wstring>::GetFileCreationTime(const std::wstring& filePath) {
	auto time = std::filesystem::last_write_time(filePath);
	auto duration = time.time_since_epoch();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
	return std::to_string(seconds);
}
template<typename T>
std::string DirectoryReader<T>::GetFileCreationTime(const std::wstring& filePath) {
	return std::string("");
}
template<>
std::vector<std::string> DirectoryReader<std::string>::GetListPathU8(const std::string& _path) {
	std::wstring pathW = Utf8ToUtf16(_path);
	return DirectoryReader<std::wstring>::GetListPathU8(pathW);
}
template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListPathU8(const std::string& _path) {
	return std::vector<std::string>();
}



template<>
std::vector<std::string> DirectoryReader<std::wstring>::GetListPathU8(const std::wstring& _path) {
	std::vector<std::wstring> PathList = DirectoryReader<std::wstring>::GetListPathW(_path);
	std::vector<std::string> PathListU8;
	for (const auto& TempElement : PathList) {
		PathListU8.push_back(Utf16ToUtf8(TempElement));
	}
	return PathListU8;
}
template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListPathU8(const std::wstring& _path) {
	return std::vector<std::string>();
}

template<>
std::vector<std::wstring> DirectoryReader<std::wstring>::GetListPathW(const std::wstring& _path) {
	std::vector<std::wstring> RealThemeList;
	for (const auto& entry : std::filesystem::directory_iterator(_path)) {
		if (entry.is_directory()) {
			RealThemeList.push_back(entry.path().wstring());
		}
	}
	return RealThemeList;
}
template<typename T>
std::vector<std::wstring> DirectoryReader<T>::GetListPathW(const std::wstring& _path) {
	return std::vector<std::wstring>();
}

template class DirectoryReader<std::wstring>;
template class DirectoryReader<std::string>;