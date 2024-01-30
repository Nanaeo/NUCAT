#pragma once

#ifndef GLOBAL_HEADER
#define GLOBAL_HEADER

#include "include/webview.h"
#include <iostream>
extern webview::webview* WebviewPtr;
extern std::map<std::string, std::string> RunTimeInfo;
#endif


// GlobalVar 全局变量储存地址