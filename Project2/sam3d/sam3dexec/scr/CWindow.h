#pragma once
#include <windows.h>
#include "../Includes/IWindow.h"         // ���������� ������������ ���� Windows
#include "../Includes/input.h"
#include "../Includes/IRender.h"
//#include "CTimer.h"

//#include <list>


#define WIN32_LEAN_AND_MEAN

namespace Sam3d
{

	class CWindow : public IWindow
	{
	public:
		CWindow(const String& caption, Dimension2d<int> windowSize, int bits, bool fullScreen, bool vsync);
	    ~CWindow(void);

		//��� ����� ����
		virtual bool Run();
		//������������ �������������/������� �������
		virtual bool switchToFullScreen(int width, int height, int bits);
		virtual void SetCaption(char* str);
		virtual bool getWinVisible();
		virtual void setWinVisible(bool set);
		virtual IRender* getRender();
		virtual ICursor* getCursor();
		//	virtual ITimer* getTimer();
		//	virtual ISceneManager* getSceneManager();
		//	virtual CInput* getInput(){return Input;};
		virtual Dimension2d<int> getWindowSize();
		class CCursor : public ICursor
		{
		public:
			CCursor(HWND hwnd, bool fullscreen) :hWnd(hwnd)
			{
				BorderX = 0;
				BorderY = 0;
				if (!fullscreen)
				{
					BorderX = GetSystemMetrics(SM_CXDLGFRAME);
					BorderY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME);
				}
			}
			~CCursor()
			{
			}

			Position2d<int> getPosition()
			{
				return Position;
			}
			void setPosition(int x, int y)
			{
				RECT rect;
				if (GetWindowRect(hWnd, &rect))
					SetCursorPos(x + rect.left + BorderX, y + rect.top + BorderY);
			}

			bool getMoved()
			{
				return Moved;
			}

			void setMoved(int move)
			{
				Moved = move;
			}

		private:

			HWND hWnd;

		};
		ICursor* Cursor = 0;
		//	CInput	*Input;

		int				bitsPerPixel = 0;	// ��� �� �������
		bool			isFullScreen = false;	// �������������?
		int				frequency = 0;		// ������� ���������� ��������
		bool ChangedToFullScreen = false;
		bool			isVisible = false;		// ���� ������?
	private:

		IRender	*Render;
		//	ISceneManager* SceneManager;
		String	Caption;
		//	ITimer	*Timer;
		Dimension2d<int> WindowSize;	//������� ����
		HWND			hWnd;			// ����� ����

		const char* title = "����";			// �������� ����
	};

};