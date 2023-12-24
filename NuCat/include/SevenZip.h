#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

class SevenZip {
public:
	SevenZip();
	~SevenZip();
	void ExtractArchive(const std::string& archive_path, const  std::string& output_path);
	void CompressFiles(const  std::string& archive_path, const vector<string>& file_paths);
private:
	void ExecuteCommand(const  std::string& command);
};