#pragma once
#include <windows.h>
#include "Vector3f.h"
#include "SColor.h"
#include "Position2d.h"

namespace Sam3d
{

//Структура вешины 3D с одной текстурой
struct S3DVertex
{
public:
	S3DVertex(){Color = SColor(0xffffffff);};
	S3DVertex(float x, float y, float z, float nx, float ny, float nz, SColor color, float u, float v)
	{
		Pos.Set(x,y,z);
		Normal.Set(nx,ny,nz);
		Color = color;
		TCoords = Position2d<float>::Position2d(u,v);
	};

	S3DVertex(const Vector3f pos, const Vector3f normal, SColor color, const Position2d<float> tCoords)
	{
		Pos = pos;
		Normal = normal;
		Color = color;
		TCoords = tCoords;
	};

	Vector3f Pos;
	Vector3f Normal;
	SColor Color;
	Position2d<float> TCoords;

};

//Структура вешины 3D с двумя текстурами
struct S3DVertex2TCoords
{
	S3DVertex2TCoords() {};
	S3DVertex2TCoords(float x, float y, float z, SColor c, float tu, float tv, float tu2, float tv2)
		: Pos(x,y,z), Color(c), TCoords(tu,tv), TCoords2(tu2,tv2) {}
	S3DVertex2TCoords(const Vector3f pos, const Vector3f normal, SColor color, const Position2d<float> tCoords,const Position2d<float> tCoords2)
	{
		Pos = pos;
		Normal = normal;
		Color = color;
		TCoords = tCoords;
		TCoords = tCoords2;
	};

	Vector3f Pos;		
	Vector3f Normal;		
	SColor Color;				
	Position2d<float> TCoords;//! First set of texture coordinates	
	Position2d<float> TCoords2;//! Second set of texture coordinates	
};

}