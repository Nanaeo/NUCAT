#include <iostream>
#include <filesystem>
std::wstring GetResourceEntry() {
	std::wstring path = std::filesystem::current_path().wstring();
	std::wstring file = L"Resource\\index.html";
	std::wstring full_path = L"file:\\\\\\" + path + L"\\" + file;
	return full_path;
}