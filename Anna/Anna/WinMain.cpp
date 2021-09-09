#include <windows.h>

#define MAX_NAME 256
#define HInstance() GetModuleHandle(NULL);

WCHAR		wdWindow[MAX_NAME];
WCHAR		wdWindowTitle[MAX_NAME];

INT			nWindowHeight;
INT			nWindowWidth;

///////////////////////////////////////////////////////////////
/// WinMain
/// Perhaps more documentation here in the future~
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{

	///////////////////////////////////////////////////////////////
	/// Init Globals
	wcscpy_s(wdWindow, TEXT("Anna"));
#ifdef _DEBUG
	wcscpy_s(wdWindowTitle, TEXT("Anna - Debug"));
#else
	wcscpy_s(wdWindowTitle, TEXT("Anna - Release"));
#endif

	nWindowWidth = 1920;
	nWindowHeight = 1080;

	///////////////////////////////////////////////////////////////
	/// Window
	WNDCLASSEX wcWindow;

	wcWindow.cbSize = sizeof(WNDCLASSEX);
	wcWindow.style = CS_HREDRAW | CS_VREDRAW;
	wcWindow.cbClsExtra = 0;
	wcWindow.cbWndExtra = 0;

	wcWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcWindow.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcWindow.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcWindow.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcWindow.lpszClassName = wdWindow;

	// We don't want a menu
	wcWindow.lpszMenuName = nullptr;

	wcWindow.hInstance = HInstance();

	// TODO: Handle changing of size, taking in signals, etc.
	wcWindow.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcWindow);

	// Display window
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
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

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