#include "Header.h"

using namespace Sam3d;


#include <Windows.h>

int  main(void)
{
	ExampleApp Root;

	if (Root.setup()) 
	{
		Root.Run();
	};
	Root.shutdown();
	return 0;
};