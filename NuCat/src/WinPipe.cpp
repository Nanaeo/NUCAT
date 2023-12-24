#include "include/WinPipe.h"
#include <iostream>

WinPipe::WinPipe() {
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    if (!CreatePipe(&read_handle_, &write_handle_, &sa, 0)) {
        return;
    }
}

WinPipe::~WinPipe() {
    CloseHandle(read_handle_);
    CloseHandle(write_handle_);
}

std::string WinPipe::RunCommand(const std::wstring& command) {
    std::string result;
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = write_handle_;
    si.hStdError = write_handle_;
    PROCESS_INFORMATION pi;
    
    if (!CreateProcessW(L"C:\\Windows\\System32\\cmd.exe", const_cast<wchar_t*>(command.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        int error = GetLastError();
        return result;
    }
    CloseHandle(pi.hThread);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    DWORD bytes_read;
    CHAR buffer[1024];
    while (ReadFile(read_handle_, buffer, sizeof(buffer), &bytes_read, NULL)) {
        result.append(buffer, bytes_read);
        if (bytes_read < sizeof(buffer)) {
            break;
        }
    }
    return result;
}

void WinPipe::SetUtf8() {
    this->RunCommand(L"chcp 65001 > nul");
}
