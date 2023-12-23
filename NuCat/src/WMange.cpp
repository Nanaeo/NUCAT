#include "include/WMange.h"

WMange::WMange(long long* HandlerFunction)
{
    LRESULT (*HandlerFunctionPtr)(HWND, UINT, WPARAM, LPARAM) = (LRESULT (*)(HWND, UINT, WPARAM, LPARAM))HandlerFunction;
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = HandlerFunctionPtr;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.lpszClassName = L"BlankWindow";
    RegisterClassW(&wc);
    m_hwnd = CreateWindowW(wc.lpszClassName, L"Blank Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, wc.hInstance, NULL);
}

WMange::~WMange()
{
    DestroyWindow(m_hwnd);
}

void WMange::Show()
{
    ShowWindow(m_hwnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hwnd);
}

HWND WMange::GetHandle() const
{
    return m_hwnd;
}
