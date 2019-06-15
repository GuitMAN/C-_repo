#include "Header.h"


int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hprevinstance,
	LPSTR lpcmdline,
	int ncmdshow)
{
	ExampleApp Root;

	if (Root.setup()) 
	{
		Root.Run();
	};
	Root.shutdown();

};