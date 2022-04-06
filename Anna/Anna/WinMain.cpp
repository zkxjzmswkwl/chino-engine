///Created by: zkxjzmswkwl
///Created on: Sept. 9, 2021.
#include "pch.h"

#ifdef _DEBUG
	#include <iostream>
	#define LOG(m) std::cout << m << "\n"
#else
	#define LOG(m)
#endif

WCHAR		wdWindow[MAX_NAME];
WCHAR		wdWindowTitle[MAX_NAME];

INT		nWindowHeight;
INT		nWindowWidth;

WNDCLASSEX	wcWindow;

enum SHUTDOWN_MSG
{
	DELIBERATE,
	CONFIG_ERR,
	DEFCON_FUCKZONE,
	AHHHHHHHHHHHHH
};

void performShutdown(SHUTDOWN_MSG eMsg)
{
	LOG(eMsg);
	exit(1);
}


void filterKeyInput(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_ESCAPE:
		performShutdown(DELIBERATE);
	}
}

LRESULT
CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			exit(1);

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void setupWindow()
{
	/// Init Globals
	wcscpy_s(wdWindow, TEXT("Anna"));
#ifdef _DEBUG
	wcscpy_s(wdWindowTitle, TEXT("Anna - Debug"));
#else
	wcscpy_s(wdWindowTitle, TEXT("Anna - Release"));
#endif

	nWindowWidth = 1920;
	nWindowHeight = 1080;

	/// Window setup
	wcWindow.cbSize = sizeof(WNDCLASSEX);
	wcWindow.style = CS_HREDRAW | CS_VREDRAW;
	wcWindow.cbClsExtra = 0;
	wcWindow.cbWndExtra = 0;

	wcWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcWindow.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcWindow.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcWindow.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcWindow.lpszClassName = wdWindow;

	/// We don't want a menu
	wcWindow.lpszMenuName = nullptr;

	wcWindow.hInstance = HInstance();

	/// TODO: Handle changing of size, taking in signals, etc.
	wcWindow.lpfnWndProc = WindowProcess;

	RegisterClassEx(&wcWindow);

	/// Display window
	HWND hWnd = CreateWindow(
		wdWindow,
		wdWindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		nWindowWidth,
		nWindowHeight,
		NULL,
		nullptr,
		wcWindow.hInstance,
		nullptr);

	if (!hWnd)
	{
		MessageBoxA(0, "Failed to create window.", NULL, MB_OK);
		return;
	}

	ShowWindow(hWnd, SW_SHOW);

}

///////////////////////////////////////////////////////////////
/// WinMain
/// Perhaps more documentation here in the future~
int
CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	setupWindow();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}
