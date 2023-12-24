#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <include/WinPipe.h>
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
    SetUtf8(){
        Write("chcp 65001\n");
    }
    void Write(const string& data) {
        DWORD bytes_written;
        if (!WriteFile(write_handle_, data.c_str(), data.size(), &bytes_written, NULL)) {
            throw runtime_error("WriteFile failed");
        }
    }

    string Read() {
        const int kBufferSize = 1024;
        char buffer[kBufferSize];
        DWORD bytes_read;
        if (!ReadFile(read_handle_, buffer, kBufferSize, &bytes_read, NULL)) {
            throw runtime_error("ReadFile failed");
        }
        return string(buffer, bytes_read);
    }

private:
    HANDLE read_handle_;
    HANDLE write_handle_;
};

int main() {
    Pipe pipe;
    pipe.Write(u8"dir\n");
    string output = pipe.Read();
    cout << output << endl;
    return 0;
}
