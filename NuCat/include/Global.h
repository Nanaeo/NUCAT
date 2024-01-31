#pragma once

#ifndef GLOBAL_HEADER
#define GLOBAL_HEADER
#include <Windows.h>
#include "include/webview.h"
#include <iostream>
extern webview::webview WebviewObject;
extern std::map<std::string, std::string> RunTimeInfo;
extern HWND WebViewHwnd;
#endif


// GlobalVar 全局变量储存地址