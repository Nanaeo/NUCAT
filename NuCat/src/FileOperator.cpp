#include "include/FileOperator.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
template<typename T>
FileOperator<T>::FileOperator(const T& inFilePath)
{
	filePath = inFilePath;
	std::fstream file(inFilePath, std::ios::in | std::ios::out | std::ios::app);
	file.close();
}
template<typename T>
FileOperator<T>::~FileOperator()
{
}
template<typename T>
bool FileOperator<T>::GetIsExists()
{
	std::fstream file(filePath, std::ios::in);
	bool exists = file.good();
	file.close();
	return exists;
}
template<typename T>
bool FileOperator<T>::ReadContent(std::string& content) const
{
	std::fstream file(filePath, std::ios::in);
	if (!file.is_open()) {
		return false;
	}
	std::getline(file, content, '\0');
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