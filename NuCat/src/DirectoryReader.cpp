#include "include/DirectoryReader.h"
#include "include/Util.h"

template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListPathU8(const T& Path)
{
	std::vector<std::string> directories;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		if (entry.is_directory()) {
			directories.push_back(entry.path().string());
		}
	}
	return directories;
}

template<typename T>
std::vector<std::wstring> DirectoryReader<T>::GetListPathW(const T& Path)
{
	std::vector<std::wstring> directories;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		if (entry.is_directory()) {
			directories.push_back(entry.path().wstring());
		}
	}
	return directories;
}

template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListFileU8(const T& Path)
{
	std::vector<std::string> FileListU8;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		auto ret = entry.path().u8string();
		FileListU8.push_back(std::string(ret.begin(), ret.end()));
	}
	return FileListU8;
}

template<typename T>
std::vector<std::wstring> DirectoryReader<T>::GetListFileW(const T& Path)
{
	std::vector<std::wstring> FileListU8;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		auto ret = entry.path().u16string();
		FileListU8.push_back(std::wstring(ret.begin(), ret.end()));
	}
	return FileListU8;
}

template<typename T>
int DirectoryReader<T>::GetFileSize(const T& Path)
{
	return static_cast<int>(std::filesystem::file_size(Path));
}

template<typename T>
std::string DirectoryReader<T>::GetFileCreationTime(const T& Path)
{
	auto time = std::filesystem::last_write_time(Path);
	auto duration = time.time_since_epoch();
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
	return std::to_string(seconds);
}

template<typename T>
bool DirectoryReader<T>::RemovePathFiles(const T& Path)
{
	for (const auto& entry : std::filesystem::recursive_directory_iterator(Path)) {
		if (entry.is_directory()) {
			std::filesystem::remove_all(entry.path());
		}
		else {
			std::filesystem::remove(entry.path());
		}
	}
	return true;
}

template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListRelativePathU8(const T& Path)
{
	std::vector<std::string> directories;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		if (entry.is_directory()) {
			auto ret = std::filesystem::relative(entry.path(),Path).u8string();
			directories.push_back(std::string(ret.begin(), ret.end()));
		}
	}
	return directories;
}

template<typename T>
std::vector<std::wstring> DirectoryReader<T>::GetListRelativePathW(const T& Path)
{
	std::vector<std::wstring> directories;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		if (entry.is_directory()) {
			auto ret = std::filesystem::relative(entry.path(), Path).u16string();
			directories.push_back(std::wstring(ret.begin(), ret.end()));
		}
	}
	return directories;
}

template<typename T>
std::vector<std::string> DirectoryReader<T>::GetListRelativeFileU8(const T& Path)
{
	std::vector<std::string> FileListU8;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		if (entry.is_regular_file()) {
			auto ret = std::filesystem::relative(entry.path(), Path).u8string();
			FileListU8.push_back(std::string(ret.begin(), ret.end()));
		}
	}
	return FileListU8;
}

template<typename T>
std::vector<std::wstring> DirectoryReader<T>::GetListRelativeFileW(const T& Path)
{
	std::vector<std::wstring> FileListU8;
	for (const auto& entry : std::filesystem::directory_iterator(Path)) {
		if (entry.is_regular_file()) {
			auto ret = std::filesystem::relative(entry.path(), Path).u16string();
			FileListU8.push_back(std::wstring(ret.begin(), ret.end()));
		}
	}
	return FileListU8;
}

template class DirectoryReader<std::wstring>;
template class DirectoryReader<std::string>;