///Created by: zkxjzmswkwl
///Created on: Sept. 9, 2021.
#include "pch.h"

#ifdef _DEBUG
	#include <iostream>
	#define LOG(m) std::cout << m << "\n"
#else
	#define LOG(m)
#endif
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"


enum SHUTDOWN_MSG
{
	DELIBERATE,
	CONFIG_ERR,
	DEFCON_FUCKZONE,
	AHHHHHHHHHHHHH
};

void PerformShutdown(SHUTDOWN_MSG eMsg)
{
	LOG(eMsg);
	exit(1);
}


///////////////////////////////////////////////////////////////
/// WinMain
/// Perhaps more documentation here in the future~
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	Window window;
	window.Setup();
	Renderer renderer(window);
	Triangle triangle(renderer);


	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		// Render
		renderer.BeginFrame();
			// Do render here
		triangle.Draw(renderer);
		renderer.EndFrame();
	}

	return 0;
}
