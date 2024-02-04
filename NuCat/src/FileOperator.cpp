#include "include/FileOperator.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <io.h>
#include <codecvt>
#include <locale>
#include "include/Util.h"
template<typename T>
FileOperator<T>::FileOperator(const T& inFilePath)
{
	filePath = inFilePath;
	std::fstream file(inFilePath, std::ios::in | std::ios::out | std::ios::app);
	file.close();
}
template<typename T>
bool FileOperator<T>::GetIsExists()
{
	std::fstream file(filePath, std::ios::in);
	bool exists = file.good();
	file.close();
	return exists;
}
//template<typename T>
//bool FileOperator<T>::ReadContent(std::string& content) const
//{
//
//	std::wfstream file;
//	file.imbue(std::locale("en_US.UTF-8"));
//	file.open(filePath, std::ios::in | std::ios::binary);
//	file.ignore((std::numeric_limits<std::streamsize>::max)());
//	file.clear(); // EOF
//	file.seekg(0, std::ios_base::beg);
//	if (!file.is_open()) {
//		return false;
//	}
//	// 获取文件大小
//	std::streampos fileSize = file.gcount();
//	auto i = (int)fileSize;
//	// 分配缓冲区
//	wchar_t* buffer = new wchar_t[fileSize];
//	if (!buffer) {
//		return false;
//	}
//	file.read(buffer, fileSize);
//	buffer[fileSize] = '\0';
//	std::wstring ret = buffer;
//	content = std::string(ret.begin(), ret.end());
//	file.close();
//	return true;
//}

template<typename T>
bool FileOperator<T>::ReadContent(std::string& content)
{

	std::locale utf8_locale(std::locale(), new std::codecvt<char, char, std::mbstate_t>);
	std::fstream file(filePath, std::ios::in | std::ios::binary);
	file.imbue(utf8_locale);
	file.ignore((std::numeric_limits<std::streamsize>::max)());
	file.clear(); // EOF
	file.seekg(0, std::ios_base::beg);
	if (!file.is_open()) {
		return false;
	}
	// 获取文件大小
	std::streampos fileSize = file.gcount();
	char* ret = new char[int(fileSize) + 1];
	// 分配缓冲区
	file.read(ret, fileSize);
	ret[fileSize] = '\0';
	content = ret;
	file.close();
	return true;
}
template<typename T>
bool FileOperator<T>::WriteContent(const  std::string& content)
{
	std::fstream file(filePath, std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		return false;
	}
	file << content;
	file.close();
	return true;
}
template<typename T>
bool FileOperator<T>::RemoveFile()
{
	if (std::filesystem::remove(filePath) != 0) {
		return false;
	}
	return true;
}
template<typename T>
bool FileOperator<T>::AppendContent(const std::string& content)
{
	std::fstream file(filePath, std::ios::out | std::ios::app);
	if (!file.is_open()) {
		return false;
	}
	file << content;
	file.close();
	return true;
}

template class FileOperator<std::wstring>;
template class FileOperator<std::string>;