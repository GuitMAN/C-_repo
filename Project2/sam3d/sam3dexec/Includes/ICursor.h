#pragma once
#include "../scr/core/Position2d.h"

namespace Sam3d
{
	class ICursor
	{
	public:
		virtual ~ICursor() {};
		virtual Position2d<int> getPosition()=0;
		virtual void setPosition(int x, int y)=0;
	};
};