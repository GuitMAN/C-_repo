#pragma once

#include "IBase.h"
#include "IFont.h"
#include "IRender.h"
#include "ICursor.h"
//#include "ITimer.h"
#include "ISceneManager.h"
#include "Input.h"

namespace Sam3d
{

class IWindow: public IBase
{
public:
	virtual ~IWindow(){};
	//Для цикла окна
	virtual bool Run()=0;
	//Переключение полноэкранный/оконный режимов
	virtual bool switchToFullScreen(int width, int height, int bits)=0;
	virtual bool getWinVisible()=0;
	virtual void setWinVisible(bool set)=0;
	virtual void SetCaption(char *str)=0;
//	virtual CInput* getInput() = 0;
	virtual IRender* getRender() = 0;
//	virtual ITimer* getTimer()= 0;
	virtual ICursor* getCursor() = 0;
	virtual ISceneManager* getSceneManager()=0;
	virtual Dimension2d<int> getWindowSize()=0;
};

};