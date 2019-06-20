#include "Header.h"



using namespace Sam3d;




int main()
{
	ExampleApp Root;

	

	if (Root.setup()) 
	{
		Root.Run();
	};
	Root.shutdown();
	return 0;
};