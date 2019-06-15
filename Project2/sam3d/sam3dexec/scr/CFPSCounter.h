#pragma once
#include "../include/types.h"

namespace Sam3d
{

class CFPSCounter  
{
public:
	CFPSCounter();

	//! returns current fps
	int getFPS();

	//! to be called every frame
	void registerFrame(uInt now);

private:

	int fps;
	uInt startTime;
	uInt framesCounted;
};

};