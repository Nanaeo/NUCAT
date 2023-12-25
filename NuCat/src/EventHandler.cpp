#include "include/EventHandler.h"
using namespace Microsoft::WRL;
ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler** CreatHandler(HWND hWnd) {
	ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler** Handler = (ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler**)malloc(sizeof(ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler));
	if (Handler == nullptr) {
		return nullptr;
	}
	Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>([hWnd](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
		env->CreateCoreWebView2Controller(hWnd, Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
			[hWnd](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
				if (controller != nullptr) {
					//建议拷贝
					webviewController = controller;
					webviewController->get_CoreWebView2(&webview);
				}
				wil::com_ptr<ICoreWebView2Settings> settings;
				webview->get_Settings(&settings);
				settings->put_IsScriptEnabled(TRUE);
				settings->put_AreDefaultScriptDialogsEnabled(TRUE);
				settings->put_IsWebMessageEnabled(TRUE);
				RECT bounds;
				GetClientRect(hWnd, &bounds);
				webviewController->put_Bounds(bounds);
				//进入默认资源入口
				webview->Navigate(GetResourceEntry().c_str());
				EventRegistrationToken token;
				webview->add_NewWindowRequested(Callback<ICoreWebView2NewWindowRequestedEventHandler>(
					[](ICoreWebView2* webview, ICoreWebView2NewWindowRequestedEventArgs* args)->HRESULT {
						wil::unique_cotaskmem_string target_uri;
						args->get_Uri(&target_uri);
						webview->Navigate(target_uri.get());
						//让uri指向当前webview
						args->put_Handled(TRUE);
						//阻止原来的逻辑
						return S_OK;
					}
				).Get(), &token);
				webview->add_NavigationStarting(Callback<ICoreWebView2NavigationStartingEventHandler>(
					[](ICoreWebView2* webview, ICoreWebView2NavigationStartingEventArgs* args) -> HRESULT {
						wil::unique_cotaskmem_string uri;
						args->get_Uri(&uri);
						std::wstring source(uri.get());
						return S_OK;
					}).Get(), &token);
				webview->add_WebMessageReceived(Callback<ICoreWebView2WebMessageReceivedEventHandler>(
					[](ICoreWebView2* webview, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
						wil::unique_cotaskmem_string message;
						args->TryGetWebMessageAsString(&message);
						if (CompareWchatText(message.get(), L"window-close")) {
							//MessageBoxW(NULL, message.get(), L"", NULL);
							//窗口关闭
							exit(0);
						}
						//webview->PostWebMessageAsString(message.get());
						return S_OK;
					}).Get(), &token);
				return S_OK;
			}).Get());
		return S_OK;
		}).CopyTo(Handler);
	return Handler;
}
