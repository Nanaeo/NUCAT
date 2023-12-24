#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class Pipe {
public:
    Pipe() {
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.lpSecurityDescriptor = NULL;
        sa.bInheritHandle = TRUE;
        if (!CreatePipe(&read_handle_, &write_handle_, &sa, 0)) {
            throw runtime_error("CreatePipe failed");
        }
    }

    ~Pipe() {
        CloseHandle(read_handle_);
        CloseHandle(write_handle_);
    }

    void Write(const wstring& data) {
        DWORD bytes_written;
        if (!WriteFile(write_handle_, data.c_str(), data.size() * sizeof(wchar_t), &bytes_written, NULL)) {
            throw runtime_error("WriteFile failed");
        }
    }

    wstring Read() {
        const int kBufferSize = 1024;
        wchar_t buffer[kBufferSize];
        DWORD bytes_read;
        if (!ReadFile(read_handle_, buffer, kBufferSize * sizeof(wchar_t), &bytes_read, NULL)) {
            throw runtime_error("ReadFile failed");
        }
        return wstring(buffer, bytes_read / sizeof(wchar_t));
    }

private:
    HANDLE read_handle_;
    HANDLE write_handle_;
};