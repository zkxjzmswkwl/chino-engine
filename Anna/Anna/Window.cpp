#include "pch.h"
#include "Window.h"
#include "Renderer.h"

Window::Window()
{
	this->nWindowWidth  = 1920;
	this->nWindowHeight = 1920;
	this->wcWindow      = { 0 };
}

void FilterKeyInput(WPARAM wParam)
{
	switch (wParam)
	{
		case VK_ESCAPE:
			exit(-1);
	}
}

LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		FilterKeyInput(wParam);

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND Window::GetHandle()
{
	return this->hWnd;
}

void Window::Setup()
{
	/// Init Globals
	wcscpy_s(wdWindow, TEXT("Chino"));
#ifdef _DEBUG
	wcscpy_s(wdWindowTitle, TEXT("Chino - Debug"));
#else
	wcscpy_s(wdWindowTitle, TEXT("Chino - Release"));
#endif

	nWindowWidth = 1920;
	nWindowHeight = 1080;

	/// Window setup
	wcWindow.style = CS_HREDRAW | CS_VREDRAW;
	wcWindow.cbClsExtra = 0;
	wcWindow.cbWndExtra = 0;

	wcWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcWindow.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcWindow.hIcon = LoadIcon(0, IDI_APPLICATION);

	wcWindow.lpszClassName = wdWindow;

	/// We don't want a menu
	wcWindow.lpszMenuName = nullptr;

	wcWindow.hInstance = HInstance();

	/// TODO: Handle changing of size, taking in signals, etc.
	wcWindow.lpfnWndProc = ProcessMessage;

	RegisterClass(&wcWindow);

	/// Display window
	hWnd = CreateWindow(
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


