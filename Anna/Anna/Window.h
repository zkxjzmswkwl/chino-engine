#pragma once
#include "pch.h"

class Window
{
public:
	Window();
	void Setup();
	HWND GetHandle();

	WNDCLASS    wcWindow;
	WCHAR		wdWindow[MAX_NAME];
	WCHAR		wdWindowTitle[MAX_NAME];

	INT		nWindowHeight;
	INT		nWindowWidth;
private:
	HWND		hWnd;
};

