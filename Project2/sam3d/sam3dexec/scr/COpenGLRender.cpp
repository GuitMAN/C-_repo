#include "COpenGLRender.h"
#include <gl\gl.h>			// ������������ ���� ��� OpenGL32 ����������

namespace Sam3d
{
	COpenGLRender::COpenGLRender(HWND hwnd, Dimension2d<int> screenSize, bool fullScreen, bool vsync)
		:hWnd(hwnd), ScreenSize(screenSize), FullScreen(fullScreen), Vsync(vsync)
	{
		              // ���������� �������� ����������

		HDC  hDC = NULL;              // ��������� �������� ���������� GDI

		HWND  hWnd = NULL;              // ����� ����� �������� ���������� ����

		HINSTANCE  hInstance;              // ����� ����� �������� ���������� ����������

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