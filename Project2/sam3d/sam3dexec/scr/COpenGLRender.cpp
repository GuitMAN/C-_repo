#include "COpenGLRender.h"
#include <gl\gl.h>			// Заголовочный файл для OpenGL32 библиотеки
#pragma comment(lib, "opengl32.lib")


namespace Sam3d
{
	COpenGLRender::COpenGLRender(HWND hwnd, Dimension2d<int> screenSize, bool fullScreen, bool vsync)
		:hWnd(&hwnd), ScreenSize(screenSize), FullScreen(fullScreen), Vsync(vsync)
	{
		   	

		Init();
	}

	COpenGLRender::~COpenGLRender()
	{
		this->Release();
	}

	bool COpenGLRender::Init()
	{
		// Set up pixel format descriptor with desired parameters
		PIXELFORMATDESCRIPTOR tmp_pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			(DWORD)(PFD_DRAW_TO_WINDOW |				// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER  |							// Must Support Double Buffering
			PFD_STEREO) ,								// Must Support Stereo Buffer
			PFD_TYPE_RGBA,								// Request An RGBA Format
			32,											// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			0,											// No Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// No Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			32,											// Z-Buffer (Depth Buffer)
			0,											// Stencil Buffer Depth
			0,											// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};
		pfd = tmp_pfd;

		if (!(hDC = GetDC(*hWnd)))              // Можем ли мы получить Контекст Устройства?
		{

			//KillGLWindow();                // Восстановить экран

			MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);

			return false;                // Вернуть false

		}

		GLuint PixelFormat = ChoosePixelFormat(hDC, &pfd);
		if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // Возможно ли установить Формат Пикселя?

		{
	//		KillGLWindow();                // Восстановить экран
			MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;                // Вернуть false

		}
			if (!(hRC = wglCreateContext(hDC)))          // Возможно ли установить Контекст Рендеринга?

			{
		//		KillGLWindow();                // Восстановить экран
				MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
				return false;                // Вернуть false
			}

		if (!wglMakeCurrent(hDC, hRC))            // Попробовать активировать Контекст Рендеринга

		{
	//		KillGLWindow();                // Восстановить экран
			MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
			return false;                // Вернуть false
		}

		return true;
	};


	void COpenGLRender::BeginScene(bool backBuffer, bool zBuffer, SColor color) 
	{
		glClear(GL_COLOR | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	};

	void COpenGLRender::EndScene()
	{
		glFlush();
		SwapBuffers(hDC);
	}
}