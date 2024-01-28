// 废弃代码 仅供参考与保存
// 新的无边框窗口由修改版 webview/webvie 完成

#include "include/WinUi.h"
#include "include/webview.h"
#include "include/Global.h"
#include <windows.h>
#include <Dwmapi.h>
#include <winuser.h>
#include <windowsx.h>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "UxTheme.lib")


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static RECT border_thickness;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		//find border thickness
		SetRectEmpty(&border_thickness);
		if (GetWindowLongPtr(hwnd, GWL_STYLE) & WS_THICKFRAME)
		{
			AdjustWindowRectEx(&border_thickness, GetWindowLongPtr(hwnd, GWL_STYLE) & ~WS_CAPTION, FALSE, NULL);
			border_thickness.left *= -1;
			border_thickness.top *= -1;
		}
		else if (GetWindowLongPtr(hwnd, GWL_STYLE) & WS_BORDER)
		{
			SetRect(&border_thickness, 1, 1, 1, 1);
		}

		MARGINS margins = { 0 };
		DwmExtendFrameIntoClientArea(hwnd, &margins);
		SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
		break;
	}
	case WM_SIZE: {
		WebviewPtr->resize_widget2();
		break;
	}
	case WM_NCACTIVATE:
		return 0;

	case WM_NCCALCSIZE:
		if (lParam)
		{
			NCCALCSIZE_PARAMS* sz = (NCCALCSIZE_PARAMS*)lParam;
			sz->rgrc[0].left += border_thickness.left;
			sz->rgrc[0].right -= border_thickness.right;
			sz->rgrc[0].bottom -= border_thickness.bottom;
			return 0;
		}
		break;

	case WM_NCHITTEST:
	{
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		ScreenToClient(hwnd, &pt);
		RECT rc;
		GetClientRect(hwnd, &rc);
		enum { left = 1, top = 2, right = 4, bottom = 8, caption = 16 };
		int hit = 0;
		if (pt.x < border_thickness.left) hit |= left;
		if (pt.x > rc.right - border_thickness.right) hit |= right;
		if (pt.y < border_thickness.top) hit |= top;
		if (pt.y > rc.bottom - border_thickness.bottom) hit |= bottom;

		//设置窗口头部30个像素可以用来拖动
		if (pt.y > border_thickness.top && pt.y < border_thickness.top + 30) hit |= caption;

		if (hit & top && hit & left) return HTTOPLEFT;
		if (hit & top && hit & right) return HTTOPRIGHT;
		if (hit & bottom && hit & left) return HTBOTTOMLEFT;
		if (hit & bottom && hit & right) return HTBOTTOMRIGHT;
		if (hit & left) return HTLEFT;
		if (hit & top) return HTTOP;
		if (hit & right) return HTRIGHT;
		if (hit & bottom) return HTBOTTOM;
		if (hit & caption) return HTCAPTION;

		return HTCLIENT;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND CreatWindowUI()
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"NuCat";
	RegisterClass(&wc);

	HWND hWnd=CreateWindowEx(0, L"NuCat", NULL,
		WS_VISIBLE | WS_THICKFRAME | WS_POPUP,
		10, 10, 650, 340, NULL, NULL, hInstance, NULL);
	return hWnd;
}