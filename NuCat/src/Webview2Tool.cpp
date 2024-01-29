#include <WebView2.h>
#include <string>
bool WebViewIsInstall()
{
	LPWSTR version_info;
	GetAvailableCoreWebView2BrowserVersionString(nullptr, &version_info);
	std::wstring VersionInfoU16(version_info);
	if (VersionInfoU16.compare(L"") == 0) return false;
	return true;
}