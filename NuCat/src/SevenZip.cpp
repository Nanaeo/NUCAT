#pragma once
#include <iostream>
#include <string>
#include <include/SevenZip.h>
using namespace std;

class SevenZip {
public:
    SevenZip() {
        ZeroMemory(&startup_info_, sizeof(startup_info_));
        startup_info_.cb = sizeof(startup_info_);
        ZeroMemory(&process_info_, sizeof(process_info_));
    }

    ~SevenZip() {
        CloseHandle(process_info_.hProcess);
        CloseHandle(process_info_.hThread);
    }

    void ExtractArchive(const string& archive_path, const string& output_path) {
        string command = "7z.exe x \"" + archive_path + "\" -o\"" + output_path + "\"";
        ExecuteCommand(command);
    }

    void CompressFiles(const string& archive_path, const vector<string>& file_paths) {
        string command = "7z.exe a \"" + archive_path + "\"";
        for (const auto& file_path : file_paths) {
            command += " \"" + file_path + "\"";
        }
        ExecuteCommand(command);
    }

private:
    void ExecuteCommand(const string& command) {
        Pipe pipe;
        ZeroMemory(&startup_info_, sizeof(startup_info_));
        startup_info_.cb = sizeof(startup_info_);
        startup_info_.dwFlags = STARTF_USESTDHANDLES;
        startup_info_.hStdInput = pipe.GetWriteHandle();
        startup_info_.hStdOutput = pipe.GetReadHandle();
        startup_info_.hStdError = pipe.GetReadHandle();
        if (!CreateProcess(NULL, const_cast<char*>(command.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &startup_info_, &process_info_)) {
            throw runtime_error("CreateProcess failed");
        }
        WaitForSingleObject(process_info_.hProcess, INFINITE);
    }
};