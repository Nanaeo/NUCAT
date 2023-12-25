#include "include/WinPipe.h"
#include <iostream>

WinPipe::WinPipe() {
    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));

    sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    if (!CreatePipe(&read_handle_, &write_handle_, &sa, 0)) {
        return;
    }
    si = { sizeof(STARTUPINFO) };
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = write_handle_;
    si.hStdError = write_handle_;
    if (!CreateProcessW(L"C:\\Windows\\System32\\cmd.exe",NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        int error = GetLastError();
    }
}

WinPipe::~WinPipe() {
    CloseHandle(read_handle_);
    CloseHandle(write_handle_);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}

std::string WinPipe::RunCommand(const std::wstring& command) {
    std::string result;
    DWORD bytes_read;
    DWORD len;
    CHAR buffer[1024];
    bool ret = WriteFile(write_handle_, const_cast<wchar_t*>(command.c_str()), sizeof(command.c_str()), &len, NULL);
    WaitForSingleObject(pi.hProcess, INFINITE);
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
