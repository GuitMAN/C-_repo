#include "CFPSCounter.h"

namespace Sam3d
{
	
CFPSCounter::CFPSCounter()
: fps(0), startTime(0), framesCounted(100)
{

}

//! returns current fps
int CFPSCounter::getFPS()
{
	return fps;
}


//! to be called every frame
void CFPSCounter::registerFrame(uInt now)
{
	framesCounted++;
	uInt milliseconds = now - startTime;

	if (milliseconds > 1000)
	{
		fps = (int)((float)framesCounted / ((float)milliseconds / 1000.0f));
		startTime = now;
		framesCounted = 0;
	}
}

};