#pragma once
#include "include/Util.h"

class WMange
{
public:
	WMange(long long* HandlerFunction, std::wstring Tittle);
	~WMange();
	void Show();

	HWND GetHandle() const;

private:
	HWND m_hwnd;
};

