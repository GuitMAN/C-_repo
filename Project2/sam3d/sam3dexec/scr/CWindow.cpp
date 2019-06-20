#include "CWindow.h"
#include <list>
#include "COpenGLRender.h"
//#include "CSceneManager.h"
//#include "CFont.h"


#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
// Файлы заголовков среды выполнения C
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
		}
		break;

		case WM_SYSCOMMAND:					// Перехватываем системную команду
		{
			switch (wParam)						// Проверяем системные вызовы
			{
			case SC_SCREENSAVE:				// Хранитель экрана пытается запуститься?
			case SC_MONITORPOWER:			// Монитор вытается уйти в спящий режим?
				return 0;						// Не надо этого всёго, пусть ничего не происходит
			}
			break;								// выход
		}
		return 0;								// выходим из функции

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_CREATE:
		{
			


		}
		return 0;

		case WM_SIZE:													// Обнаружена смена размера окна
			switch (wParam)												// Вычислим какая
			{
			case SIZE_MINIMIZED:		// Окно минимизировано?
				if (win)win->isVisible = false;
				return 0;
			case SIZE_MAXIMIZED:		// Окно максимизировано?
				if (win)win->isVisible = true;
				// Подгоняем окно - LoWord=Width, HiWord=Height
				return 0;
			case SIZE_RESTORED:			// Окно было востановлено?
				if (win)win->isVisible = true;
				// Подгоняем - LoWord=Width, HiWord=Height
				return 0;
			}
			return 0;

		case WM_KEYDOWN:
		{
			if ((wParam >= 0) && (wParam <= 255))
			{
				//				win->Input->keys.keyDown [wParam] = true;
				//				win->Input->lastKeyDown = (OIS::KEY_CODES)wParam;
			}
		}
		return 0;

		// Если введен символ
		case WM_CHAR:
			// Если консоль видима
		{
			// Если символ видимый
			if ((wParam > 31) && (wParam != '`'))
			{
				// Добавляем в командую строчку консоли
				////MainConsole->Current+=(char)wParam;
			}
		}
		break;

		case WM_LBUTTONDOWN:								// Left mouse button is pressed
//			win->Input->Mouse.LButtonDown=TRUE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_RBUTTONDOWN:								// Right mouse button is pressed
			win = getDeviceFromHWnd(hWnd);
			//		win->Input->Mouse.RButtonDown=TRUE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_MBUTTONDOWN:								// Middle mouse button is pressed
//			win->Input->Mouse.MidButtonDown=TRUE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_MBUTTONUP:								// Middle mouse button is pressed
//			win->Input->Mouse.MidButtonDown=FALSE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_LBUTTONUP:								// Left mouse button is pressed
//			win->Input->Mouse.LButtonDown=FALSE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_RBUTTONUP:								// Right mouse button is pressed
//			win->Input->Mouse.RButtonDown=FALSE;
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_KEYUP:
		{
			if ((wParam >= 0) && (wParam <= 255))
			{
				//				win->Input->keys.keyDown [wParam] = false;	
				//				win->Input->lastKeyDown = (OIS::KEY_CODES)wParam;
				return 0;
			}
		}
		return 0;

		case WM_MOUSEMOVE:
		{
			win->Cursor->setPosition(LOWORD(lParam), HIWORD(lParam));
			win->Cursor->setMoved(1) ;
		}
		return 0;
		case WM_MOUSEWHEEL:
		{
			//			win->Input->Mouse.Wheel= (int)wParam;
		}
		return 0;

		case WM_DESTROY:
		{
			
		}
		return 0;

		case WM_CLOSE:			// Закрываем окно
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
			
			return 0;
		}
		}
		return (DefWindowProc(hWnd, msg, wParam, lParam));
	};

	CWindow::CWindow(const String& caption, Dimension2d<int> windowSize, int bits, bool fullScreen, bool vsync) :
		isFullScreen(fullScreen), Caption(caption)

	{

		HINSTANCE hInstance = GetModuleHandle(0);
		WNDCLASSEX windowsclass; // Создем класс
		const char* className = "SWindow";
		// Создаем дескриптор окна
		 // Сообщение
// Определим класс окна WNDCLASSEX
		windowsclass.cbSize = sizeof(WNDCLASSEX);
		windowsclass.style = CS_HREDRAW | CS_VREDRAW;
		windowsclass.lpfnWndProc = (WNDPROC)MsgProc;
		windowsclass.cbClsExtra = 0;
		windowsclass.cbWndExtra = 0;
		windowsclass.hInstance = hInstance;
		windowsclass.hIcon = NULL;
		windowsclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowsclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		windowsclass.lpszMenuName = NULL;
		windowsclass.lpszClassName = className;
		windowsclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		// Зарегестрируем класс
		if (!RegisterClassEx(&windowsclass)) {
			
			return;
		}
			//	UnregisterClass(windowsclass.lpszClassName,windowsclass.hInstance);
				// Теперь когда класс зарегестрирован можно создать окно
		
		
		
		RECT clientSize;
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = windowSize.Width;
		clientSize.bottom = windowSize.Height;
		if (!fullScreen)
			clientSize.bottom += 27;

		DWORD style = WS_POPUP;

		if (!isFullScreen)
		{
			style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
		}
		AdjustWindowRect(&clientSize, style, FALSE);

		if (!(hWnd = CreateWindowExA(NULL,				// стиль окна
			className,	// класс
			Caption.c_str(),    // название окна
			style, //WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			0, 0,				// левый верхний угол
			windowSize.Width, windowSize.Height,				// ширина и высота
			NULL,					// дескриптор родительского окна 
			NULL,					// дескриптор меню
			hInstance, // дескриптор экземпляра проложенния
			NULL)))					// указатель на данные созданного окна
			return;
		

		Cursor = new CCursor(hWnd, isFullScreen);

	

		ShowWindow(hWnd, SW_SHOWDEFAULT);    //Нарисуем окно    
		UpdateWindow(hWnd);                  //Обновим окно
		ShowCursor(true);
		isVisible = true;
		if (isFullScreen) switchToFullScreen(windowSize.Width, windowSize.Height, bits);

		Render = new COpenGLRender(hWnd, windowSize, fullScreen, vsync);
		if (!Render->Init())
		{
			MessageBox(HWND_DESKTOP, "Не удалось инициализировать OpenGL", "Error", MB_OK | MB_ICONEXCLAMATION);
			Render->Release();
			return;
		};

		//	Input = new CInput();
		
		//	Timer = new CTimer();

		//	SceneManager = CreateSceneManager(Render,Timer);

		SEnvMapper em;
		em.SamWin = this;
		em.hWnd = hWnd;
		EnvMap.push_back(em);


		SetActiveWindow(hWnd);
		SetForegroundWindow(hWnd);

	};

	CWindow::~CWindow()
	{
		
		
		
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
};