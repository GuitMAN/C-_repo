#include "Header.h"



using namespace Sam3d;




int APIENTRY  wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	ExampleApp Root;

	

	if (Root.setup()) 
	{
		
		Root.Run();
		
	};
	Root.shutdown();
	return 0;
};