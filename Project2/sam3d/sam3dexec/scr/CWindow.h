#pragma once

#include "../Includes/IWindow.h"         // ���������� ������������ ���� Windows
#include "../Includes/input.h"
//#include "CTimer.h"

//#include <list>


#define WIN32_LEAN_AND_MEAN

namespace Sam3d
{

class CWindow: public IWindow
{
public:
	CWindow(const String& caption, Dimension2d<int> windowSize,  int bits, bool fullScreen, bool vsync);
	virtual ~CWindow(void);

	//��� ����� ����
	bool Run();
	//������������ �������������/������� �������
	virtual bool switchToFullScreen(int width, int height, int bits);
	virtual void SetCaption(char *str);
	virtual bool getWinVisible();
	virtual void setWinVisible(bool set);
	virtual IRender* getRender();
	virtual ICursor* getCursor();
//	virtual ITimer* getTimer();
	virtual ISceneManager* getSceneManager();
//	virtual CInput* getInput(){return Input;};
	virtual Dimension2d<int> getWindowSize();
	class CCursor: public ICursor
	{
	public:
		CCursor(HWND hwnd, bool fullscreen):hWnd(hwnd),Moved(false)
		{	
			BorderX = 0;
			BorderY = 0;
			if (!fullscreen)
			{
				BorderX = GetSystemMetrics(SM_CXDLGFRAME);
				BorderY = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYDLGFRAME);
			}
		}
		~CCursor(){};
		virtual Position2d<int> getPosition()
		{

            return Position;
		}
		void setPosition(int x, int y)
		{
			RECT rect;
			if (GetWindowRect(hWnd, &rect))
				SetCursorPos(x + rect.left + BorderX, y + rect.top + BorderY);
		}
		bool Moved;
		Position2d<int> Position; 
		HWND hWnd;
		int BorderX, BorderY;
	};
	CCursor *Cursor;
//	CInput	*Input;

	int				bitsPerPixel;	// ��� �� �������
	bool			isFullScreen;	// �������������?
	int				frequency;		// ������� ���������� ��������
	bool ChangedToFullScreen;
	bool			isVisible;		// ���� ������?
private:

	IRender	*Render;
	ISceneManager* SceneManager;
	String	Caption;
//	ITimer	*Timer;
	Dimension2d<int> WindowSize;	//������� ����
	HWND			hWnd;			// ����� ����

	char*			title;			// �������� ����
};

};