#pragma once
#include "../Includes/IRender.h"
#include "../Includes/ISceneNode.h"
#include "../scr/core/Position2d.h"

namespace Sam3d
{

	class IFont : public  ISceneNode
	{
	public:
		virtual ~IFont() {};
		virtual bool Load(char* name);
		virtual void Draw(char* name, SColor color, Position2d<int>& position);
		virtual void Render() {};


	};

};