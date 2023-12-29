#include "include/WinUi.h"
#include "include/webview.h"
#include "include/Global.h"
#include <windows.h>
#include <Dwmapi.h>

#pragma comment(lib,"Dwmapi.lib")

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_NCCALCSIZE:
	{
		if (wParam == TRUE)
		{
			SetWindowLong(hWnd, 0, 0);
			return TRUE;
		}
		return FALSE;
	}
	case WM_SIZE: {
		WebviewPtr->resize_widget2();
		break;
	}
	case WM_NCHITTEST:
	{
		// 获取光标位置
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		// 获取窗口大小
		RECT rc;
		GetClientRect(hWnd, &rc);

		// 设置边框大小
		const int BORDER_WIDTH = 10;

		// 检查光标是否在边框上
		if (pt.x < BORDER_WIDTH) // 左边框
		{
			if (pt.y < BORDER_WIDTH)
				return HTTOPLEFT; // 左上角
			if (pt.y > rc.bottom - BORDER_WIDTH)
				return HTBOTTOMLEFT; // 左下角
			return HTLEFT; // 左边框
		}
		if (pt.x > rc.right - BORDER_WIDTH) // 右边框
		{
			if (pt.y < BORDER_WIDTH)
				return HTTOPRIGHT; // 右上角
			if (pt.y > rc.bottom - BORDER_WIDTH)
				return HTBOTTOMRIGHT; // 右下角
			return HTRIGHT; // 右边框
		}
		if (pt.y < BORDER_WIDTH)
			return HTTOP; // 上边框
		if (pt.y > rc.bottom - BORDER_WIDTH)
			return HTBOTTOM; // 下边框
		return HTCAPTION; // 标题栏
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps{ 0 };
		HDC hdc = BeginPaint(hWnd, &ps);
		// Draw with GDI+ to make sure the alpha channel is opaque.
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


HWND CreatWindowUI()
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Sample Window Class";
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 设置光标
	RegisterClass(&wc);

	HWND hWnd = CreateWindowEx(0, L"Sample Window Class", L"Sample Window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		return 0;
	}

	MARGINS margins = { 0, 0, 0, 1 };
	DwmExtendFrameIntoClientArea(hWnd, &margins);

	SetWindowPos(hWnd, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	ShowWindow(hWnd, 0);
	return hWnd;
}