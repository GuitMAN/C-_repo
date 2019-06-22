#include "CWindow.h"
#include <list>
#include "COpenGLRender.h"
//#include "CSceneManager.h"
//#include "CFont.h"


#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows
#include <windows.h>
// ����� ���������� ����� ���������� C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

namespace Sam3d
{


	struct SEnvMapper
	{
		HWND hWnd;
		CWindow* SamWin;
	};

	std::list<SEnvMapper> EnvMap;

	SEnvMapper* getEnvMapperFromHWnd(HWND hWnd)
	{
		std::list<SEnvMapper>::iterator it = EnvMap.begin();
		for (; it != EnvMap.end(); ++it)
			if ((*it).hWnd == hWnd)
				return &(*it);

		return 0;
	}

	CWindow* getDeviceFromHWnd(HWND hWnd)
	{
		std::list<SEnvMapper>::iterator it = EnvMap.begin();
		for (; it != EnvMap.end(); ++it)
			if ((*it).hWnd == hWnd)
				return (*it).SamWin;

		return 0;
	}


	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif
#ifndef WHEEL_DELTA                     
#define WHEEL_DELTA 120
#endif

		CWindow * win = 0;
		win = getDeviceFromHWnd(hWnd);


		switch (msg)
		{
		case WM_ACTIVATE:	// Activate Message
		{
			if (win) win->isVisible = true;

			if (win && win->isFullScreen)
			{
				if ((wParam & 0xFF) == WA_INACTIVE)
				{
					// If losing focus we minimize the app to show other one
					ShowWindow(hWnd, SW_MINIMIZE);
					// and switch back to default resolution
					win->switchToFullScreen(win->getWindowSize().Width, win->getWindowSize().Height, win->bitsPerPixel);
				}
				else
				{
					// Otherwise we retore the fullscreen Irrlicht app
					SetForegroundWindow(hWnd);
					ShowWindow(hWnd, SW_RESTORE);
					// and set the fullscreen resolution again
					win->switchToFullScreen(win->getWindowSize().Width, win->getWindowSize().Height, win->bitsPerPixel);
				}
			}
		}
		break;

		case WM_SYSCOMMAND:					// ������������� ��������� �������
		{
			// prevent screensaver or monitor powersave mode from starting
			if ((wParam & 0xFFF0) == SC_SCREENSAVE ||
				(wParam & 0xFFF0) == SC_MONITORPOWER ||
				(wParam & 0xFFF0) == SC_KEYMENU
				)
				return 0;				// �����
		}
		break;								// ������� �� �������

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;

		case WM_CREATE:
		{



		}
		break;

		case WM_SIZE:													// ���������� ����� ������� ����
			switch (wParam)												// �������� �����
			{
			case SIZE_MINIMIZED:		// ���� ��������������?
				if (win)win->isVisible = false;
				return 0;
			case SIZE_MAXIMIZED:		// ���� ���������������?
				if (win)win->isVisible = true;
				// ��������� ���� - LoWord=Width, HiWord=Height
				return 0;
			case SIZE_RESTORED:			// ���� ���� ������������?
				if (win)win->isVisible = true;
				// ��������� - LoWord=Width, HiWord=Height
				return 0;
			}
			break;


		case WM_SETCURSOR:
			// because Windows forgot about that in the meantime
			
			if (win)
			{
			//	win->getCursor()->setActiveIcon(win->getCursorControl()->getActiveIcon());
			//	win->getCursor()->setVisible(dev->getCursorControl()->isVisible());
			}
			break;


		case WM_KEYDOWN:
		{
			if ((wParam >= 0) && (wParam <= 255))
			{
				//				win->Input->keys.keyDown [wParam] = true;
				//				win->Input->lastKeyDown = (OIS::KEY_CODES)wParam;
			}
		}
		break;

		// ���� ������ ������
		case WM_CHAR:
			// ���� ������� ������
		{
			// ���� ������ �������
			if ((wParam > 31) && (wParam != '`'))
			{
				// ��������� � �������� ������� �������
				////MainConsole->Current+=(char)wParam;
			}
		}
		break;

		case WM_LBUTTONDOWN:								// Left mouse button is pressed
//			win->Input->Mouse.LButtonDown=TRUE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_RBUTTONDOWN:								// Right mouse button is pressed
			win = getDeviceFromHWnd(hWnd);
			//		win->Input->Mouse.RButtonDown=TRUE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_MBUTTONDOWN:								// Middle mouse button is pressed
//			win->Input->Mouse.MidButtonDown=TRUE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_MBUTTONUP:								// Middle mouse button is pressed
//			win->Input->Mouse.MidButtonDown=FALSE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_LBUTTONUP:								// Left mouse button is pressed
		{
			//			win->Input->Mouse.LButtonDown=FALSE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		case WM_RBUTTONUP:								// Right mouse button is pressed
		{
			//			win->Input->Mouse.RButtonDown=FALSE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			break;
		}
		case WM_KEYUP:
		{
			if ((wParam >= 0) && (wParam <= 255))
			{
				//				win->Input->keys.keyDown [wParam] = false;	
				//				win->Input->lastKeyDown = (OIS::KEY_CODES)wParam;

			}

			break;
		}
		case WM_MOUSEMOVE:
		{
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			win->Cursor->setMoved(1);
		}
		break;
		case WM_MOUSEWHEEL:
		{
			//			win->Input->Mouse.Wheel= (int)wParam;
		}
		break;

		case WM_DESTROY:
		{

		}
		break;

		case WM_CLOSE:			// ��������� ����
		{

			std::list<SEnvMapper>::iterator it = EnvMap.begin();
			for (; it != EnvMap.end(); ++it)
			{
				if ((*it).hWnd == hWnd)
				{
					EnvMap.erase(it);
					break;
				}
			}
			DestroyWindow(hWnd);

			//	if (SceneManager) SceneManager->Release();
			//	if (Input) delete Input;
			//	if (Timer) Timer->Release();
			if (win->ChangedToFullScreen) {};
			if (win->getRender()) win->getRender()->Release();
			if (win->Cursor) delete win->Cursor;

			ChangeDisplaySettings(NULL, 0);

			PostQuitMessage(0);
			PostMessage(hWnd, WM_QUIT, 0, 0);

			break;
		}
		}
		return (DefWindowProc(hWnd, msg, wParam, lParam));
	}

	CWindow::CWindow(const String& caption, Dimension2d<int> windowSize, int bits, bool fullScreen, bool vsync) :
		isFullScreen(fullScreen), Caption(caption)

	{

		HINSTANCE hInstance = GetModuleHandle(0);
		WNDCLASSEX windowsclass; // ������ �����
		const char* className = "SWindow";
		// ������� ���������� ����
		 // ���������
// ��������� ����� ���� WNDCLASSEX
		windowsclass.cbSize = sizeof(WNDCLASSEX);
		windowsclass.style = CS_HREDRAW | CS_VREDRAW;
		windowsclass.lpfnWndProc = MsgProc;
		windowsclass.cbClsExtra = 0;
		windowsclass.cbWndExtra = 0;
		windowsclass.hInstance = hInstance;
		windowsclass.hIcon = NULL;
		windowsclass.hCursor = 0; LoadCursor(NULL, IDC_ARROW);
		windowsclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		windowsclass.lpszMenuName = NULL;
		windowsclass.lpszClassName = className;
		windowsclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		// �������������� �����
		RegisterClassEx(&windowsclass);
	//		
			// ������ ����� ����� ��������������� ����� ������� ����

		RECT clientSize;
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = windowSize.Width;
		clientSize.bottom = windowSize.Height;

		if (!fullScreen)
			clientSize.bottom += 27;

		DWORD style = WS_POPUP;
		int top = 50, left = 50;
		if (!isFullScreen)
		{
			style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
			top = 0;
			left = 0;
		}

		AdjustWindowRect(&clientSize, style, FALSE);

		if (!(hWnd = CreateWindow(className,	// �����
			Caption.c_str(),    // �������� ����
			style, //WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			top, left,				// ����� ������� ����
			windowSize.Width, windowSize.Height,				// ������ � ������
			NULL,					// ���������� ������������� ���� 
			NULL,					// ���������� ����
			hInstance, // ���������� ���������� �����������
			NULL)))					// ��������� �� ������ ���������� ����
			return;

		ShowWindow(hWnd, SW_SHOWNORMAL);    //�������� ����    
		UpdateWindow(hWnd);                  //������� ����
//		ShowCursor(true);
		isVisible = true;
		if (isFullScreen) switchToFullScreen(windowSize.Width, windowSize.Height, bits);

		Cursor = new CCursor(hWnd, isFullScreen);
		SEnvMapper em;
		em.SamWin = this;
		em.hWnd = hWnd;
		EnvMap.push_back(em);

		Render = new COpenGLRender(hWnd, windowSize, fullScreen, vsync);
		if (!Render->Init())
		{
			MessageBox(HWND_DESKTOP, "�� ������� ���������������� OpenGL", "Error", MB_OK | MB_ICONEXCLAMATION);
			Render->Release();
			return;
		};

		//	Input = new CInput();
		//	Timer = new CTimer();
		//	SceneManager = CreateSceneManager(Render,Timer);

		SetActiveWindow(hWnd);
		SetForegroundWindow(hWnd);

//		if (MessageBox(NULL, (LPCSTR)"������ �� �� ��������� ���������� � ������������� ������?",
//			(LPCSTR)"��������� � ������������� ������?", 			MB_YESNO | MB_ICONQUESTION) == IDNO)
//			isFullScreen = false;          // ������� �����
	};

	CWindow::~CWindow()
	{

		const char* className = "SWindow";
		UnregisterClass(className, windowsclass.hInstance);


	};

	bool CWindow::switchToFullScreen(int width, int height, int bits)
	{
		DEVMODE dm;
		memset(&dm, 0, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmPelsWidth = width;
		dm.dmPelsHeight = height;
		dm.dmDisplayFrequency = 85;
		dm.dmBitsPerPel = 32;
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		LONG ret = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);

		switch (ret)
		{
		case DISP_CHANGE_SUCCESSFUL:
			ChangedToFullScreen = true;
			return true;
		case DISP_CHANGE_RESTART:
			return false;
		case DISP_CHANGE_BADFLAGS:
			return false;
		case DISP_CHANGE_BADPARAM:
			return false;
		case DISP_CHANGE_FAILED:
			return false;
		case DISP_CHANGE_BADMODE:
			return false;
		}

		return false;
	};

	bool CWindow::getWinVisible()
	{
		return isVisible;
	};

	void CWindow::setWinVisible(bool set)
	{
		isVisible = set;
	};
	void CWindow::SetCaption(char* str)
	{
		SetWindowText(hWnd, str);
	};

	bool CWindow::Run()
	{
		MSG msg;
		bool quit = false;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				quit = true;
		}
		//	if (!quit)
			//	resizeIfNecessary();

		//	Render->registerFrame(Timer->getTime());

		return !quit;
	};

	IRender* CWindow::getRender()
	{
		return Render;
	}

	ICursor* CWindow::getCursor()
	{
		return Cursor;
	}

	//ITimer* CWindow::getTimer()
	//{
	//	return Timer;
	//}

	//ISceneManager* CWindow::getSceneManager()
	//{
	//	return SceneManager;
	//};

	Dimension2d<int> CWindow::getWindowSize()
	{
		return WindowSize;
	};



	IWindow* createWindow(const String& caption, Dimension2d<int> windowSize, int bits, bool fullScreen, bool vsync)
	{
		CWindow* Win;
		Win = new CWindow(caption, windowSize, bits, fullScreen, vsync);

		if (Win && !Win->getRender())
		{
			Win->Release();
			Win = 0;
		}
		return Win;
	};




	/*
	#ifdef __cplusplus
		extern "C" {     // do not use C++ decorations
	#endif

			DLL_API IWindow* DLLCALLCONV createWindow(const String& caption, Dimension2d<int> windowSize, int bits, bool fullScreen, bool vsync)
			{
				CWindow* Win;
				Win = new CWindow(caption, windowSize, bits, fullScreen, vsync);

	//			if (Win && !Win->getRender())
				{
					Win->Release();
					Win = 0;
				}
				return Win;
			};



	#ifdef __cplusplus
		} // close extern C
	#endif
	*/
}