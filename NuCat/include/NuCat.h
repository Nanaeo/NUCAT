#pragma once
#include "Header.h"
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <wrl.h>
#include <wil/com.h>
#include <WebView2EnvironmentOptions.h>
#include "WebView2.h"
static wil::com_ptr<ICoreWebView2Controller> webviewController;
static wil::com_ptr<ICoreWebView2> webview;
//Global Var