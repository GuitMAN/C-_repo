#include "COpenGLRender.h"
#include <gl\gl.h>			// Заголовочный файл для OpenGL32 библиотеки

namespace Sam3d
{
	COpenGLRender::COpenGLRender(HWND hwnd, Dimension2d<int> screenSize, bool fullScreen, bool vsync)
		:hWnd(hwnd), ScreenSize(screenSize), FullScreen(fullScreen), Vsync(vsync)
	{
		              // Постоянный контекст рендеринга

		HDC  hDC = NULL;              // Приватный контекст устройства GDI

		HWND  hWnd = NULL;              // Здесь будет хранится дескриптор окна

		HINSTANCE  hInstance;              // Здесь будет хранится дескриптор приложения

		Init();
	}

	COpenGLRender::~COpenGLRender()
	{
		this->Release();
	}

	bool COpenGLRender::Init()
	{

		return 0;
	};

}