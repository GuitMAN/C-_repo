#pragma once
#include <stdio.h>
#include <string>



namespace Sam3d
{

#define Log     Message()   



	static class Logger
	{
	public:
		Logger()
		{
			printf("%s Start Application \r\n", __TIMESTAMP__);
		}
	
		~Logger()
		{
		}

		void Write(const char* String)
		{
			printf("%s %s\r", __TIMESTAMP__,  String);
		}

	};



	inline Logger& Message()
	{
		static Logger SingleObject;
		return SingleObject;
	}
}