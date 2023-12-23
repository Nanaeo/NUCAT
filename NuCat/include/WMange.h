#pragma once
#include "include/Util.h"

class WMange
{
public:
	WMange(long long* HandlerFunction);
	~WMange();
	void Show();

	HWND GetHandle() const;

private:
	HWND m_hwnd;
};

